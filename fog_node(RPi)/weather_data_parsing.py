import json

with open('weather.json') as json_file:
    data = json.load(json_file)
    count = 0
    flag = 0
    str=""
    f = open('parsed_weather_data.txt','w')
    for p in data['list']:
        for q in p['weather']:
            if count < 16:
                count += 1	
                str = str+q['main']+","	
            else : 
                    flag = 1
                    break
        f.write(str)
        if flag == 1 : 
            break
    f.close()

