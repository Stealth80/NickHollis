--Nick Hollis
--This simple query uses Inner Joins to join tables and limits the results to internationalship true and a date range
--Names of tables and and columns have been changed to generic names

SELECT S.shipdate AS 'Ship Date', ST.country AS 'Destination Country', F.description AS 'FOB', SO.shippedamt AS 'Value (Shipped Amount)', S.ffcompname AS 'Freight Forwarder Name', S.packnum AS 'Pack Number', SO.ordernum AS 'Order Number'
FROM ship AS S
Inner Join ShipmentOrder AS SO ON (S.packnum = SO.packnum AND S.company = SO.company)
Inner Join ShipTo AS ST ON (S.custnum = ST.custnum AND S.Num = ST.Num AND S.company = ST.company)
Inner Join Orders AS O ON (SO.ordernum = O.ordernum AND SO.company = O.company)
Inner Join FOB AS F ON (O.fob = F.fob)
WHERE S.intrntlship <> '0'
AND S.shipdate > '2014/01/01'
AND S.shipdate < (SELECT GETDATE())
Order By SO.ordernum
