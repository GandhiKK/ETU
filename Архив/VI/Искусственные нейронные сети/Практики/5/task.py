import os
from re import X
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '1' 
import pandas as pd
import numpy as np
import tensorflow.keras
from tensorflow.keras import layers
from sklearn.preprocessing import LabelEncoder
from tensorflow.keras.utils import to_categorical
from tensorflow.keras.models import Sequential, Model
from tensorflow.keras.layers import Dense, Input
import matplotlib.pyplot as plt
from matplotlib import gridspec
from keras.models import load_model
import gen_data

def create_ae():
    encoding_dim = 8

    # Энкодер
    input_data = Input(shape=(6,))
    x = Dense(encoding_dim*4, activation='relu', name='enc1')(input_data)
    x = Dense(encoding_dim*3, activation='relu', name='enc2')(x)
    encoded = Dense(encoding_dim, name='encout')(x)

    # Декодер
    x = Dense(encoding_dim*3, activation='relu', name='dec1')(encoded)
    x = Dense(encoding_dim*4, activation='relu', name='dec2')(x)
    decoded = Dense(6, name='decout')(x)

    # Регрессия
    x = Dense(64, activation='relu', name='reg1')(encoded)
    x = Dense(48, activation='relu', name='reg2')(x)
    x = Dense(32, activation='relu', name='reg3')(x)
    regression = Dense(1, name='regout')(x)

    model = Model(inputs=[input_data], outputs=[regression, decoded])
    denses = [input_data, encoded, decoded, regression]
    return model, denses

gen_data.solution()

train_data = np.genfromtxt('train_data.csv', delimiter=';')
train_targets = np.genfromtxt('train_targets.csv', delimiter=';')
test_data = np.genfromtxt('test_data.csv', delimiter=';')
test_targets = np.genfromtxt('test_targets.csv', delimiter=';')

model, denses = create_ae()

# Обучаем
model.compile(optimizer='adam', loss='mse', metrics=['mae'], loss_weights=[1., 0.5])
model.fit([train_data], [train_targets, train_data], epochs=200, batch_size=25, validation_data=([test_data], [test_targets, test_data]))

# Разбиваем и сохраняем результаты
enc_model = Model(inputs=[denses[0]], outputs=[denses[1]])
enc_pred = enc_model.predict(test_data)
np.savetxt('encoded.csv', enc_pred, delimiter=';')
enc_model.save('encoded.h5')

input_enc = Input(shape=(8,))
x = model.get_layer("dec1")(input_enc)
x = model.get_layer("dec2")(x)
decout = model.get_layer("decout")(x)
dec_model = Model(input_enc, decout)
dec_pred = dec_model.predict(enc_pred)
np.savetxt("decoded.csv", dec_pred, delimiter=';')
dec_model.save('decoded.h5')

regr_model = Model(inputs=[denses[0]], outputs=[denses[3]])
regr_pred = regr_model.predict(test_data)
np.savetxt('regression.csv', regr_pred, delimiter=';')
regr_model.save('regression.h5')

