all:
	g++ cerebro.cpp -o cerebro -pthread

clean:
	rm cerebro

install:
	install -Dm755 "./cerebro" "/usr/sbin/cerebro"
	install -Dm755 "./cerebro.service" "/usr/lib/systemd/system/cerebro.service"
