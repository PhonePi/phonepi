all:
	g++ cerebro.cpp -o cerebro -pthread

clean:
	rm cerebro

install:
	install -Dm755 "./cerebro" "$(DESTDIR)/sbin/cerebro"
	install -Dm755 "./cerebro.service" "$(DESTDIR)/lib/systemd/system/cerebro.service"
