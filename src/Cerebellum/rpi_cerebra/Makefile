all:
	g++ cerebro.cpp -o cerebro -pthread

clean:
	rm cerebro

install:
	install -Dm755 "./cerebro" "$(DESTDIR)/usr/sbin/cerebro"
	install -Dm755 "./cerebro.service" "$(DESTDIR)/usr/lib/systemd/system/cerebro.service"
