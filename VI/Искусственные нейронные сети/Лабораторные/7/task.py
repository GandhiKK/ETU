import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'
os.environ['TF_FORCE_GPU_ALLOW_GROWTH'] = 'true'
from matplotlib import gridspec
import re
import matplotlib
import matplotlib.pyplot as plt
import numpy as np
from keras.utils import to_categorical
from keras.layers import Dense, Dropout, LSTM, Conv1D, MaxPool1D, GRU, Flatten
from keras.models import Sequential
from keras.layers.embeddings import Embedding
from keras.preprocessing import sequence
from sklearn.metrics import accuracy_score

from keras.datasets import imdb
(training_data, training_targets), (testing_data, testing_targets) = imdb.load_data(num_words=10000)
data = np.concatenate((training_data, testing_data), axis=0)
targets = np.concatenate((training_targets, testing_targets), axis=0)

X_test = data[:10000]
Y_test = targets[:10000]
X_train = data[10000:]
Y_train = targets[10000:]

max_review_length = 500 # макс. длина текста
embedding_vecеor_length = 32 # 32-мерное векторное представление
top_words = 10000 # количество слов, рассматриваемых как признаки

X_train = sequence.pad_sequences(X_train, maxlen=max_review_length)
X_test = sequence.pad_sequences(X_test, maxlen=max_review_length)

model_a = Sequential([
    Embedding(top_words, embedding_vecеor_length, input_length=max_review_length),
    Conv1D(64, 3, padding='same', activation='relu'),
    MaxPool1D(2),
    Dropout(0.3),
    Conv1D(128, 3, padding='same', activation='relu'),
    MaxPool1D(2),
    Dropout(0.2),
    LSTM(64, return_sequences=True, dropout=0.2),
    LSTM(32),
    Dense(1, activation='sigmoid')])

model_b = Sequential([
    Embedding(top_words, embedding_vecеor_length, input_length=max_review_length),
    LSTM(100, return_sequences=True, dropout=0.3),
    LSTM(50, dropout=0.3),
    Dense(1, activation='sigmoid')])

model_c = Sequential([
    Embedding(top_words, embedding_vecеor_length, input_length=max_review_length),
    Conv1D(32, 3, padding='same', activation='relu'),
    MaxPool1D(2),
    Dropout(0.5),
    Conv1D(64, 3, padding='same', activation='relu'),
    MaxPool1D(2),
    Dropout(0.4),
    Flatten(),
    Dense(128),
    Dropout(0.5),
    Dense(1, activation='sigmoid')])

ans_len = 3
train_size, test_size = len(X_train) // ans_len, len(X_test) // ans_len

members = [model_a, model_b, model_c]
epochs = [2, 2, 3]
for i, mod in enumerate(members):
    x_train = X_train[i * train_size : (i + 1) * train_size]
    y_train = Y_train[i * train_size : (i + 1) * train_size]
    x_test = X_test[i * test_size : (i + 1) * test_size]
    y_test = Y_test[i * test_size : (i + 1) * test_size]
    mod.compile(loss='binary_crossentropy', optimizer='adam', metrics=['accuracy'])
    mod.fit(x_train, y_train, validation_split=0.1, epochs=epochs[i], batch_size=64)
    scores = mod.evaluate(x_test, y_test, verbose=2)
    print("Accuracy: %.2f%%" % (scores[1]*100))

def stacked_prediction(members, x_test, load=False):
    yhat = []
    for i, m in enumerate(members):
        if load:
            print(m.predict(x_test, verbose=0))
        yhat.append(np.round(m.predict(x_test, verbose=0)))
    yhat = np.asarray(yhat)
    yhat = [np.round(np.mean(x)) for x in zip(*yhat)]
    return np.asarray(yhat).astype('int')

yhat = stacked_prediction(members, X_test)
acc = accuracy_score(Y_test, yhat)
print("Accuracy: %.2f%%" % (acc*100))

def load_text():
    dictionary = imdb.get_word_index()
    load_x = []
    words = input()
    words = re.sub(r"[^a-zA-Z0-9']", " ", words)
    words = words.split(' ')
    valid = []
    for word in words:
        word = dictionary.get(word)
        if word in range(1, 10000):
            valid.append(word+3)
    load_x.append(valid)
    result = sequence.pad_sequences(load_x, maxlen=max_review_length)
    print(stacked_prediction(members, result, True))

load_text()