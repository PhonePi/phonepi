all:
	g++ cerebro.cpp -o cerebro -pthread

clean:
	rm cerebro

install:
	mkdir -p "$(DESTDIR)/usr/bin"
	mkdir -p "$(DESTDIR)/usr/lib/systemd/system/cerebro.service"
	install -m755 "./cerebro" "$(DESTDIR)/usr/bin/cerebro"
	install -m755 "./cerebro.service" "$(DESTDIR)/usr/lib/systemd/system/cerebro.service"
