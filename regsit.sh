#!/bin/bash

#get cookie
curl -c cookie.txt -A "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.0)" -H "Accept-Language: en-us,en;q=0.5" http://222.24.19.190:8080/portal/index_default.jsp &>/dev/null

ip=$(ifconfig | egrep 'inet addr:222' | cut -d: -f2 | awk '{print $1}')
#ip=$(ifconfig | egrep '222' | awk '{print $2}')
user=wangluo3
pwd=h3c64321

PostData="userName=$user&userPwd=$(echo -n $pwd | base64)&serviceType=&isSavePwd=on&userurl=http%3A%2F%2Fwww.baidu.com&userip=$ip&basip=&language=Chinese&portalProxyIP=222.24.19.190&portalProxyPort=50200&dcPwdNeedEncrypt=1&assignIpType=0&assignIpType=0&appRootUrl=http://222.24.19.190:8080/portal/&manualUrl=&manualUrlEncryptKey=rTCZGLy2wJkfobFEj0JF8A=="

while true;
do
    ping -c 1 www.baidu.com -W 1 &>/dev/null;
    if [ "$?" == "0" ]; then
        echo 1234
        sleep 1;
    else
        curl -b cookie.txt -A "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.0)" -H "Accept-Language: en-us,en;q=0.5" -d "$PostData" "http://222.24.19.190:8080/portal/pws?t=li" >/dev/null;
        echo  adbfasdf
        sleep 1;
    fi
done
