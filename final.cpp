/*
 * =====================================================================================
 *
 *       Filename:  simple.cpp
 *
 *    Description:  最简单的http
 *
 *        Version:  1.0
 *        Created:  2015年06月01日 15时52分32秒
 *       Revision:  none
 *       Compiler:  clang 
 *
 *         Author:  magichan (fgm), 574932286@qq.com
 *   Organization:  FH Südwestfalen, Iserlohn
 *           Rule:  ???? question 
 *                  [    comment
 *
 * =====================================================================================
 */
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<map>
#include<time.h>
#include<curl/curl.h>
#include<unistd.h>
#include<sys/time.h>
#include<signal.h>
#include<string.h>
#include"base64.h"
#define DEBUGENDABLDE 1
#define DEBUG(fmt,...) do {\
        if(DEBUGENDABLDE) \
        fprintf (stderr, fmt, ##__VA_ARGS__); \
}\
while (0)
#define ID "wangluo4"
#define KEY "h3c654321"
#define COOK "cookies.txt"
#define HEATBEATPOSTFIEL "heatbeatpostfile"
int alarmcount=0;
char  a[100] = "http://www.baidu.com";
char b[100]="http://222.24.19.190:8080/portal/index_default.jsp";
char c[100]="http://222.24.19.190:8080/portal/pws?t=li";
char d[100]="http://222.24.19.190:8080/portal/pws?t=hd";

void set_curl_local_port(CURL * curl );
int post_id_key(char * li, const char * id , const char * key ,const char * cookiesfile);
int get_cookies(const char * cookies_url,const  char  * cookies_file );
int  cheackInert(char * url);
void make_a_heat(char * url);
int  cheackInert(char * url)
{
        FILE * temp;
        time_t timep;
        CURLcode ret;
        temp = fopen("film","w");
        CURL * curl;
        curl = curl_easy_init();
        curl_easy_setopt(curl,CURLOPT_URL,url);
        curl_easy_setopt(curl,CURLOPT_WRITEDATA,temp);
        ret = curl_easy_perform(curl);
        
        if( ret != CURLE_OK)
        {
                time(&timep);
                std::cout<<ctime(&timep)<<" "<<"Intnet can't be accesed "<<std::endl;
                curl_easy_cleanup(curl);
                return 1;
        }
        time(&timep);
        std::cout<<ctime(&timep)<<" "<<"Intnet  be accesed "<<std::endl;

        curl_easy_cleanup(curl);
        return 0;
}
int insert_http_head(CURL * curl )
{
        curl_easy_setopt(curl,CURLOPT_USERAGENT,"Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.0)");

        struct curl_slist * headers = NULL;
        headers = curl_slist_append(headers,"Connection: keep-alive");
        headers = curl_slist_append(headers,"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8");
        headers = curl_slist_append(headers,"Accept-Language: en-us,en;q=0.6");
        curl_easy_setopt(curl,CURLOPT_HTTPHEADER,headers);
        return 0;

}
/* get cookies into the file*/
int get_cookies(const char * cookies_url,const  char  * cookies_file )
{
        CURL * curl;
        CURLcode ret;
        curl = curl_easy_init();
        FILE * html_fp = fopen("html","w");
        

        if(curl)
        {
                insert_http_head(curl);
                ret = curl_easy_setopt(curl,CURLOPT_URL,cookies_url);
                curl_easy_setopt(curl,CURLOPT_WRITEDATA,html_fp);
                /*put get html file to html_fp */
                ret = curl_easy_setopt(curl,CURLOPT_COOKIEJAR,cookies_file);
                if( ret!= CURLE_OK )
                {
                        fprintf(stderr, "Curl perform failed: %s\n", curl_easy_strerror(ret));
                        return 1;
                }

                ret = curl_easy_perform(curl);

                if( ret!= CURLE_OK )
                {
                        fprintf(stderr, "Curl perform failed: %s\n", curl_easy_strerror(ret));
                        return 1;
                }

                curl_easy_cleanup(curl);
                fclose(html_fp);
        }
        time_t timep;
        time(&timep);
        std::cout<<ctime(&timep)<<" GET COOKIES , PUT IT INOT FIFE"<<std::endl;
        return 0;
        
}
/* 发送key 成功返回1 失败返回0*/
int post_id_key(char * li, const char * id , const char * key ,const char * cookiesfile)
{
        CURL * curl;
        CURLcode ret;
        curl = curl_easy_init();
        FILE * html_fp = fopen(HEATBEATPOSTFIEL,"w");
        
        /*make the post content*/
        const std::string id_string("userName=");
        const std::string key_string("&userPwd=");
        const std::string last("&serviceType=&isSavePwd=on&userurl=http%3A%2F%2Fwww.baidu.com&userip=$ip&basip=&language=Chinese&portalProxyIP=222.24.19.190&portalProxyPort=50200&dcPwdNeedEncrypt=1&assignIpType=0&assignIpType=0&appRootUrl=http://222.24.19.190:8080/portal/&manualUrl=&manualUrlEncryptKey=rTCZGLy2wJkfobFEj0JF8A==");
        const std::string s = key ;
        std::string encoded = base64_encode(reinterpret_cast<const unsigned char*>(s.c_str()), s.length());

        std::string target = id_string+id+key_string+encoded+last ;
        const char * target_ptr = target.c_str();

        /*make a cookies */
        std::string hi("hello");
        std::string cookies_start = hi+"1="+id+"; "+hi+"2=false; "+hi+"3=; "+hi+"=4; ";

        if(curl)
        {
                insert_http_head(curl);
                curl_easy_setopt(curl,CURLOPT_URL,li);
                //const char* charptr_cookies_start = cookies_start.c_str();
               // ret = curl_easy_setopt(curl,CURLOPT_COOKIE,charptr_cookies_start);
               
                curl_easy_setopt(curl,CURLOPT_COOKIEFILE,cookiesfile);
                /*set cookies */
                curl_easy_setopt(curl,CURLOPT_WRITEDATA,html_fp);
                /*drop html*/
               // curl_easy_setopt(curl,CURLOPT_POSTFIELDSIZE,(long)strlen(target_ptr));
                curl_easy_setopt(curl,CURLOPT_POSTFIELDS,target_ptr);
                /*POST*/
                
                ret = curl_easy_perform(curl);
               if( ret!= CURLE_OK )
                {
                          std::cout<<"curl_easy_perform() fall "<<curl_easy_strerror(ret)<<std::endl;
                          std::cout<<"post failed "<<std::endl;
                          return 0;
                }
                fclose(html_fp);
                curl_easy_cleanup(curl);
                time_t timep;
                time(&timep);
                std::cout<<ctime(&timep)<<"  POST KEY & ID"<<std::endl;
                return 1;
                
        }else{
                curl_easy_cleanup(curl);
                time_t timep;
                time(&timep);
                std::cout<<"curl_easy_init() fall "<<curl_easy_strerror(ret)<<std::endl;
                std::cout<<ctime(&timep)<<"post failed "<<std::endl;
                return 0;
        }

}
void make_a_heat(char * url)
{
        CURL * curl;
        curl = curl_easy_init();
        CURLcode ret;
        std::string target("userip=&basip=&userDevPort=YDDX-NQ-HX-S1250-vlan-03-0251%40vlan&userStatus=99&serialNo=7761&language=Chinese&e_d=");

        const char * target_ptr = target.c_str();
        if(curl)
        {
                insert_http_head(curl);
                curl_easy_setopt(curl,CURLOPT_URL,url);
                curl_easy_setopt(curl,CURLOPT_COOKIEJAR,HEATBEATPOSTFIEL);
                curl_easy_setopt(curl,CURLOPT_POSTFIELDS,target_ptr);
                ret = curl_easy_perform(curl);
                if(ret != CURLE_OK )
                {
                          std::cout<<"curl_easy_perform() fall "<<curl_easy_strerror(ret)<<std::endl;
                          std::cout<<" heat failed "<<std::endl;
                          exit(0);
                }
                time_t timep;
                time(&timep);
                std::cout<<ctime(&timep)<<"Make A HEAT "<<std::endl;
                curl_easy_cleanup(curl);
        }
        else{
                std::cout<<"curl_easy_init() error "<<std::endl;
                std::cout<<"heat failed"<<std::endl;
        }
        
}
int main()
{

        CURL * curl;
        CURLcode res;
        int trycount = 0 ;
        
        curl_global_init(CURL_GLOBAL_ALL);
        /*初始话*/
        get_cookies(b,COOK);
        /*获取cookies*/
        post_id_key(c,ID,KEY,COOK);

        /* 发送密码和用户
        */
        while(1)
        {
                trycount++;
                if(trycount==120)
                {
                        make_a_heat(d);
                        /*10分钟一次心跳包*/
                        trycount = 0;
                }
                sleep(5);
                /*等待5s*/
                int cout=0;
                while(cheackInert(a))
                {
                        /*网络断开，重新登陆*/
                       post_id_key(c,ID,KEY,COOK);
                       cout++;
                       if(cout%10 == 0 )
                       {
                        
                               time_t rawtime;
                               struct tm * timeinfo;

                               time(&rawtime);
                               timeinfo = localtime(&rawtime);
                               
                               std::ofstream log("regist.log",std::ios::app);
                               log<<asctime(timeinfo)<<" "<<"多次登陆尝试失败"<<std::endl;
                               log.close();
                       }

                }

        }
        curl_global_cleanup();

        return 0;
}
