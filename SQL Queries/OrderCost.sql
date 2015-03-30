--Nick Hollis
--This example uses 2 subqueries and 2 subquery pivot tables
--Names of tables and and columns have been changed to generic names

SELECT od.number, o.orderdate, c.custid, od.char01 AS 'Coordinator', od.part, od.qty, w.code, jp.jobnum, jb.startdate, ep.EstSetupHours, ap.ActSetupHours, ep.EstInstallHours, ap.ActInstallHours, j.EstLaborHours AS 'EstTotalInstallHours', j.ActualLaborHours  AS 'ActualTotalInstallHours', j.CrewSize, (j.ActualLaborHours*j.CrewSize) AS 'TotalLabor', m.ActualMtlCost, j.ActualLaborCost, (j.ActualLaborCost+m.ActualMtlCost) AS 'Total Install Cost', (od.qty*od.price) AS 'Total Price of Install Line', ((od.qty*od.price)-(j.ActualLaborCost+m.ActualMtlCost)) AS 'Total Profit', jb.jobstatus AS 'Status', od.comments
FROM OrdDetail od
INNER JOIN Orders o ON (od.company = o.company AND od.number = o.number)
INNER JOIN Warehouse w ON (od.company = w.company AND od.part = w.part)
INNER JOIN Customer c ON (od.company = c.company AND od.custnum = c.custnum)
INNER JOIN OrderRel Rel ON (od.company = Rel.company AND od.number = Rel.number AND od.Line = Rel.Line)
INNER JOIN JobProd jp ON (od.company = jp.company AND od.number = jp.number AND od.Line = jp.Line)
INNER JOIN Job jb ON (jp.company = jb.company AND jp.jobnum = jb.jobnum)

INNER JOIN 

(SELECT jp.company, jp.jobnum, od.part, jo.crewsize, SUM(estprodhours) AS 'EstLaborHours', SUM(actprodhours) AS 'ActualLaborHours', SUM(actlabcost) AS 'ActualLaborCost'
			FROM OrdDetail od
			INNER JOIN JobProd jp ON (od.company = jp.company AND od.number = jp.number AND od.Line = jp.Line)
			INNER JOIN JobOperationation jo ON (jp.company = jo.company AND jp.jobnum = jo.jobnum)
			INNER JOIN job jb ON (jp.company = jb.company AND jp.jobnum = jb.jobnum)
			WHERE jb.JobF = 1
			GROUP BY jp.company, jp.JobNum, od.part, jo.crewsize) AS j
ON (jp.company = j.company AND jp.jobnum = j.jobnum AND jp.part = j.part)

INNER JOIN 

(SELECT jp.company, jp.jobnum, jp.part, SUM(requiredqty*estunitcost) AS 'EstMtlCost', SUM(totalcost) AS 'ActualMtlCost'
	FROM OrdDetail od
	INNER JOIN JobProd jp ON (od.company = jp.company AND od.number = jp.number AND od.Line = jp.Line)
	INNER JOIN JobMaterial jm ON (jp.company = jm.company AND jp.jobnum = jm.jobnum)
	INNER JOIN job jb ON (jp.company = jb.company AND jp.jobnum = jb.jobnum)
	WHERE jb.JobF = 1
	GROUP BY jp.company, jp.JobNum, jp.part) AS m
ON (jp.company = m.company AND j.jobnum = m.jobnum AND jp.part = m.part)

INNER JOIN

(select company, jobnum, [20] AS 'EstSetupHours', [10] AS 'EstInstallHours'
	from (select company, jobnum, estprodhours, oprseq from JobOperation) AS estprodhrs
	pivot (sum(estprodhours) for oprseq in ([10], [20])) as ephppvt) AS ep
ON (jp.company = ep.company AND jp.jobnum = ep.jobnum)

INNER JOIN

(select company, jobnum, [20] AS 'ActSetupHours', [10] AS 'ActInstallHours'
	from (select company, jobnum, actprodhours, oprseq from JobOperation) AS actprodhrs
	pivot (sum(actprodhours) for oprseq in ([10], [20])) as aphpvt) AS ap
ON (jp.company = ap.company AND jp.jobnum = ap.jobnum)

WHERE w.code = 'Warehouse-1'
AND jb.JobF = 1
Order By od.number, od.Line