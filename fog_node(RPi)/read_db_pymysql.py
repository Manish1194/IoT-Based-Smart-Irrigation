import relay_script
import pymysql

try:
    mySQLconnection = pymysql.connect(host='--------',database='---------',user='--------',password='--------',unix_socket='/var/run/mysqld/mysqld.sock')
    sql_select_Query = "select * from sensor_values order by timestamp desc "
    cursor = mySQLconnection .cursor()
    cursor.execute(sql_select_Query)
    records = cursor.fetchone()
    mySQLconnection.commit()
    cursor.close()
    mySQLconnection.close()
    
    print("timestamp = ", records[0])
    print("Soil_moisture = ",records[1])
    print("water level  = ", records[2])
    print("Nitrogen  = ", records[3])
    print("Phosphrous  = ", records[4])
    print("Potassium  = ", records[5])
    
    
    list=[]
    count=0
    rain=0
    
    c = csv.writer(open("temp.csv","wb"))
    c.writerow(result)
    
    sm_threshold=500
    sm_threshold=50
    f=open('/home/pi/parsed_weather_data.txt','r')
    str=f.read()
    list=str.split(":")
    for l in list:
        if l is "rain":
            count+=1;
    if count <= 4 :
        rain=1
    else: 
        rain=0    
    if  float(records[2]) <= wl_threshold && float(records[1]) >=sm_threshold && rain==0 :      
        execfile('relay_script.py') 
    elif float(records[2]) <= wl_threshold && float(records[1]) <=sm_threshold :
        print("no irrigation is required")
    cursor.close()
finally:
    #closing database connection.
    mySQLconnection.commit()
    print("MySQL connection is closed")


