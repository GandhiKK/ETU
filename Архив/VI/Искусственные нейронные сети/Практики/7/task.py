import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'
os.environ['TF_FORCE_GPU_ALLOW_GROWTH'] = 'true'
import math
import random
from keras.layers import GRU, LSTM, Dense, Dropout
import numpy as np
from tensorflow.keras.models import Sequential
import matplotlib.pyplot as plt
from matplotlib import gridspec


def func(i):
    return ((i % 20) + 1) / 20

def gen_sequence(seq_len=1000):
    seq = [abs(math.sin(i/20)) + func(i) + random.normalvariate(0, 0.04)
           for i in range(seq_len)]
    return np.array(seq)

def gen_data_from_sequence(seq_len = 1000, lookback = 10):
    seq = gen_sequence(seq_len)
    past = np.array([[[seq[j]] for j in range(i,i+lookback)] for i in range(len(seq) - lookback)])
    future = np.array([[seq[i]] for i in range(lookback,len(seq))])
    return (past, future, seq)

def draw_sequence(seq):
    plt.plot(range(len(seq)), seq, 'r-', label='Signal')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.legend()
    plt.tight_layout()
    plt.show()


data, res, seq = gen_data_from_sequence()
draw_sequence(seq)

dataset_size = len(data)
train_size = (dataset_size // 10) * 7
val_size = (dataset_size - train_size) // 2

train_data, train_res = data[:train_size], res[:train_size]
val_data, val_res = data[train_size:train_size+val_size], res[train_size:train_size+val_size]
test_data, test_res = data[train_size+val_size:], res[train_size+val_size:]


model = Sequential([
    GRU(60, recurrent_activation='sigmoid', return_sequences=True, recurrent_dropout=0.1),
    LSTM(40,  return_sequences=True,  recurrent_dropout=0.1),
    GRU(30, activation='relu', recurrent_dropout=0.1),
    Dense(1)
])

model.compile(optimizer='adam', loss='mse')
history = model.fit(train_data, train_res, epochs=50, validation_data=(val_data, val_res))

loss = history.history['loss']
val_loss = history.history['val_loss']
plt.plot(range(len(loss)), loss, 'r-', label='Training loss')
plt.plot(range(len(val_loss)), val_loss, 'b--', label='Validation loss')
plt.title('Training and validation loss')
plt.xlabel('Epochs')
plt.ylabel('Loss')
plt.legend()
plt.tight_layout()
plt.show()

predicted_res = model.predict(test_data)
pred_length = range(len(predicted_res))
plt.plot(pred_length, predicted_res, 'g-', label='Predicted res')
plt.plot(pred_length, test_res, 'r-', label='True res')
plt.tight_layout()
plt.legend()
plt.show()