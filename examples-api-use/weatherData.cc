#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

int main(void)
{
  CURL *curl;
  CURLcode response;
  curl_global_init(CURL_GLOBAL_ALL);
  curl=curl_easy_init(); 

  //-75.0046,40.0623999

  if(curl){
    curl_easy_setopt(curl,CURLOPT_URL, "https://api.weather.gov/gridpoints/PHI/54,82/forecast");
    //curl_easy_setopt(curl,CURLOPT_URL, "https://api.weather.gov/points/40.0623999,-75.0046/forecast"); <- doesn't work for some reason
    //curl_easy_setopt(curl,CURLOPT_URL, "https://api.open-meteo.com/v1/forecast?latitude=39.9523&longitude=-75.1638&daily=sunrise,sunset&hourly=temperature_2m,precipitation_probability,rain&current=temperature_2m&timezone=America%2FNew_York&wind_speed_unit=mph&temperature_unit=fahrenheit&precipitation_unit=inch");
    curl_easy_setopt(curl,CURLOPT_USERAGENT,"User Agent: mjsavas9@gmail.com");

    response=curl_easy_perform(curl);

    if(response!= CURLE_OK){
      fprintf(stderr, "Request failed: %s\n", curl_easy_strerror(response));

    }else {
      printf("%u",response);
    }
    curl_easy_cleanup(curl);

  }
  curl_global_cleanup();
  return 0;
}