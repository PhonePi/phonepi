all:
	g++ cerebro.cpp -o cerebro -pthread

clean:
	rm cerebro

install:
	install -Dm755 "./cerebro" "$(DESTDIR)/usr/bin/cerebro"
	install -Dm755 "./cerebro.service" "$(DESTDIR)/usr/lib/systemd/system/cerebro.service"
