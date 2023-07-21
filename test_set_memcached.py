# get existance probability
# then set value to memcached

import time
import requests

from pymemcache.client.base import Client

def get_probability():
  response = requests.get('RequestURL')
  rawtext = response.text.split('\n')
  cam1 = rawtext[0].split(',')[2]
  cam2 = rawtext[1].split(',')[2]
  # print(cam1, cam2)
  return  cam1, cam2

def main():
  client = Client(('localhost', 11211))
  while True:
    cam1, cam2 = get_probability()
    print(cam1, cam2)
    client.set('cam1', cam1)
    client.set('cam2', cam2)
    # r = client.get('cam1')
    # print('cam1:', r)
    # r2 = client.get('cam2')
    # print('cam2:', r2)
    time.sleep(1)

if __name__ == "__main__":
  main()
