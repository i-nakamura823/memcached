# Memcached
Ubuntu環境でmemcachedを使うためのテスト

c++、pythonでMemcachedを使うための練習

## ① Ubuntu環境にインストール
```
sudo apt update
sudo apt install memcached
sudo apt install libmemcached-tools
```
開始
```
sudo systemctl start memcached
```
確認
```
sudo ss -plunt
```
[How To Install and Secure Memcached on Ubuntu 20.04](https://www.digitalocean.com/community/tutorials/how-to-install-and-secure-memcached-on-ubuntu-20-04)

## ②´ c++の場合
1. libmemcachedのインストール
```
tar zxvf libmemcached-0.21.tar.gz
cd libmemcached-0.21.tar.gz

./configure
make
sudo make install
```
[libmemcached公式](https://libmemcached.org/libMemcached.html) からとってくる

2. libmemcachedを含めてコンパイル
```
g++ a.cpp -lmemcached  -v
./a.out
```

## ②´ pythonの場合
1. pymemccachedのインストール
```
pip install pymemcache
```
2. 使う
```
from pymemcache.client.base import Client
client = Client(('localhost', 11211))
 
# SET
client.set('some_key', 'some_value')
 
#GET
result = client.get('some_key')
```
[参考URL：pymemcacheを使ってPythonからMemcachedにアクセス](https://self-development.info/pymemcache%E3%82%92%E4%BD%BF%E3%81%A3%E3%81%A6python%E3%81%8B%E3%82%89memcached%E3%81%AB%E3%82%A2%E3%82%AF%E3%82%BB%E3%82%B9/)

