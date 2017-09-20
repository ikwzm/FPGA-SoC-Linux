import msgpackrpc

cli = msgpackrpc.Client(msgpackrpc.Address('127.0.0.1', 54321))

for i in range(44):
	result = cli.call('fib', i)
	print("%d => %d" % (i, result))

cli.close()

