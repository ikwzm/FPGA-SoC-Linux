cp fibonacci_server.bin /lib/firmware/fibonacci_server.bin
dtbocfg.rb --install fibonacci_server --dts fibonacci_server.dts

socat -d -d tcp-listen:54321,fork /dev/zptty0,raw,nonblock,echo=0 &

