# Deploy F-Stack on AWS EC2 in one minute

  If you have a Redhat7.3 EC2 instance，and then execute the following cmds, you will get the F-Stack server in one minute 

    sudo -i
    yum install -y xxxx
	mkdir /data/f-stack
	git clone https://github.com/F-Stack/f-stack.git /data/f-stack

    # Compile DPDK
	make config T=x86_64-native-linuxapp-gcc
	make

    # set hugepage	
	echo 1024 > /sys/kernel/mm/hugepages/hugepages-2048kB/nr_hugepages
	mkdir /mnt/huge
	mount -t hugetlbfs nodev /mnt/huge

    # insmod ko
    modprobe uio.ko
    insmod x86_64-native-linuxapp-gcc/build/kmod/igb_uio.ko
    insmod x86_64-native-linuxapp-gcc/build/kmod/rte_kni.ko

    # set ip address
    export myaddr=`ifconfig eth0 | grep "inet" | grep -v ":" | awk -F ' '  '{print $2}'`
    export mymask=`ifconfig eth0 | grep "netmask" | awk -F ' ' '{print $4}'`
    export mybc=`ifconfig eth0 | grep "broadcast" | awk -F ' ' '{print $6}'`
    export myhw=`ifconfig eth0 | grep "ether" | awk -F ' ' '{print $2}'`
    export mygw=`route -n | grep 0.0.0.0 | grep eth0 | grep UG | awk -F ' ' '{print $2}'`
    sed "s/addr=192.168.1.2/addr=${myaddr}/" -i /data/f-stack/config.ini
    sed "s/netmask=255.255.255.0/netmask=${mymask}/" -i /data/f-stack/config.ini
    sed "s/broadcast=192.168.1.255/broadcast=${mybc}/" -i /data/f-stack/config.ini
    sed "s/gateway=192.168.1.1/gateway=${mygw}/" -i /data/f-stack/config.ini

    # enable kni
    sed "s/#\[kni\]/\[kni\]/" -i /data/f-stack/config.ini
    sed "s/#enable=1/enable=1/" -i /data/f-stack/config.ini
    sed "s/#method=reject/method=reject/" -i /data/f-stack/config.ini
    sed "s/#tcp_port=80/tcp_port=80/" -i /data/f-stack/config.ini

	# Compile F-Stack lib
	export FF_PATH=/data/f-stack
	export FF_DPDK=/data/f-stack/dpdk/x86_64-native-linuxapp-gcc/lib
    cd /data/f-stack/lib
	make

    # Compile Nginx
    cd app/nginx-1.11.10
	./configure --prefix=/usr/local/nginx_fstack --with-ff_module
	make
	make install

    # offload NIC
    ifconfig eth0 down
	python /data/f-stack/tools/dpdk-devbind.py --bind=igb_uio eth0

    # start Nginx
    cd ../..
	./start.sh -b /usr/local/nginx_fstack/sbin/nginx -c config.ini

    # start kni
    sleep 30
    ifconfig veth0 ${myip}  netmask ${mymask}  broadcast ${mybc} hw ether ${myhw}
    route add -net 0.0.0.0 gw ${mygw} dev veth0