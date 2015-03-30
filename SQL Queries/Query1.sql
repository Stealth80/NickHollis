--This example of SQL code uses 2 queries using NOT IN and a subquery to arrive at a result.  
--The first subquery uses a Left Outer Join as well as Inner Joins while the subquery in the second query is simple.
--Names of tables and and columns have been changed to generic names

SELECT Number, partdescription, class, typecode
FROM Part 
WHERE typecode = 'a_code_type'
AND part.Number NOT IN (SELECT m.Number FROM Material AS m
							INNER JOIN Part AS p ON (m.Num = p.Number AND m.company = p.company)
							INNER JOIN Warehouse AS w ON (m.Num = w.Number AND m.company = w.company)
							INNER JOIN Plant AS p ON (m.Num = p.Number AND m.company = p.company)
							LEFT OUTER JOIN PartDetail AS pd ON (m.Number = pd.Number AND m.company = pd.company)
							INNER JOIN PartRev AS pr ON (m.Number = pr.Number AND m.rev = pr.rev AND m.method = pr.method AND m.company = pr.company)
							WHERE w.code = 'warehouse-1'
							AND pr.aproved = 1
							AND p.typecode = 'a_code_type')
ORDER BY Number


SELECT Number, partdescription, class, typecode
FROM Part 
WHERE typecode = 'a_code_type'
AND Number NOT IN (SELECT Number FROM Material)