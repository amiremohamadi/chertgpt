CC=g++

chertgpt: *.cc dataset.txt
	$(CC) *.cc -o chertgpt

dataset.txt:
	curl -o dataset.txt https://raw.githubusercontent.com/karpathy/char-rnn/master/data/tinyshakespeare/input.txt
