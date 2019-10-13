
import pymysql
import os
import requests


def notification(check_level,str):
        payload="sender_id=--------------"+ "\n" +"ATTENTION!" + "\n"
        
        if(check_level!=2):   
            
            if(check_level == 1 ):
                level="low"
            else:
                level="very low"
            
            tt=" is "
            
            check_level=int(check_level)
            if(str=="nitrogen"):
                fertilizer="Please apply Urea."
            elif( str=="potassium"):
                fertilizer="Please apply  Potassium Sulphate for  ."+str+" "
            elif(str=="phosphorous"):
                fertilizer="Please apply DAP for  ."+str+" "
            else:
                fertilizer=""
                level=""
                tt=""
                
                
            url = "https://www.fast2sms.com/dev/bulk"
            payload = payload +str +tt+level+" \n " +fertilizer+"&language=english&route=p&numbers=----------"
            headers = {
        	'authorization': "------------------------------------------------------------------------",
        	'Content-Type': "------------------------------------",
        	'Cache-Control': "----------",
                }
            response = requests.request("POST", url, data=payload, headers=headers,verify=False)
            print(response)
            print("Message Send")


