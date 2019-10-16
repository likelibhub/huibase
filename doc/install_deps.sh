

apt-get update
apt-get upgrade -y
apt-get install libmysqlclient-dev -y
apt-get install perl -y

# openssl
cd ../deps/
tar xvfz openssl.tar.gz
rm -f openssl.tar.gz
cd openssl
export LC_ALL="en_US.UTF-8"
export CFLAGS=-fPIC
./config shared zlib
make -j4
cd ..


# curl
tar xvfz curl.tar.gz
rm -f curl.tar.gz
cd curl
./configure --without-ssl
make -j4
cd ..

# libmemcached
tar xvfz libmemcached.tar.gz
rm -f libmemcached.tar.gz
cd libmemcached
./configure
make -j4
cd ..

# hiredis
tar xvfz hiredis.tar.gz
rm -f hiredis.tar.gz
cd hiredis
make -j4
cd ..


