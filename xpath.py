import xml.etree.ElementTree as ET


tree = ET.parse("./xmlfile.xml")
a = tree.findall('//a[*]/c[d]')
for i in a:
    st = ET.tostring(i).decode("utf-8") 
    print(st)
