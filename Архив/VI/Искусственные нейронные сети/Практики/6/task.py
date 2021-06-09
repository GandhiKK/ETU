import os
from re import M
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'
os.environ['TF_FORCE_GPU_ALLOW_GROWTH'] = 'true'
from sklearn.preprocessing import LabelEncoder
from matplotlib import gridspec
import matplotlib.pyplot as plt
from tensorflow.keras.layers import Dense
from tensorflow.keras.models import Sequential
import numpy as np
from keras.layers import Input, Conv2D, MaxPooling2D, Dense, Dropout, Flatten
from keras.metrics import Precision, Recall


def gen_rect(size=50):
    img = np.zeros([size, size])
    x = np.random.randint(0, size)
    y = np.random.randint(0, size)
    w = np.random.randint(size // 10, size // 2)
    h = np.random.randint(size // 10, size // 2)
    img[x:x + w, y:y + h] = 1
    return img


def gen_circle(size=50):
    img = np.zeros([size, size])
    x = np.random.randint(0, size)
    y = np.random.randint(0, size)
    r = np.random.randint(size // 10, size // 3)
    for i in range(0, size):
        for j in range(0, size):
            if (i-x)**2 + (j-y)**2 <= r**2:
                img[i, j] = 1
    return img


def gen_data(size=500, img_size=50):
    c1 = size // 2
    c2 = size - c1
    label_c1 = np.full([c1, 1], 'Square')
    data_c1 = np.array([gen_rect(img_size) for i in range(c1)])
    label_c2 = np.full([c2, 1], 'Circle')
    data_c2 = np.array([gen_circle(img_size) for i in range(c2)])
    data = np.vstack((data_c1, data_c2))
    label = np.vstack((label_c1, label_c2))
    return data, label


def data_preprocessing(X, Y):
    encoder = LabelEncoder()
    y = encoder.fit_transform(Y.ravel())

    idx = np.random.permutation(len(X))
    X, y = X[idx], y[idx]

    val_split = 0.1
    test_num = round((1-val_split)*len(X))
    val_num = round(test_num*(1-val_split))
    train_data, train_labels = X[:val_num], y[:val_num]
    val_data, val_labels = X[val_num:test_num], y[val_num:test_num]
    test_data, test_labels = X[test_num:], y[test_num:]
    train_data = np.expand_dims(train_data, axis=3)
    val_data = np.expand_dims(val_data, axis=3)
    test_data = np.expand_dims(test_data, axis=3)
    return (train_data, val_data, test_data), (train_labels, val_labels, test_labels)


def draw_results(H):
    loss = H.history['loss']
    val_loss = H.history['val_loss']
    acc = H.history['accuracy']
    val_acc = H.history['val_accuracy']
    epochs = range(1, len(loss) + 1)

    fig = plt.figure(figsize=(12, 6))
    gs = gridspec.GridSpec(1, 2, width_ratios=[3, 3])
    plt.subplot(gs[0])
    plt.plot(epochs, loss, 'r--', label='Training loss')
    plt.plot(epochs, val_loss, 'g--', label='Validation loss')
    plt.title('Training and validation loss')
    plt.xlabel('Epochs')
    plt.ylabel('Loss')
    plt.legend()

    plt.subplot(gs[1])
    plt.plot(epochs, acc, 'r--', label='Training acc')
    plt.plot(epochs, val_acc, 'g--', label='Validation acc')
    plt.title('Training and validation accuracy')
    plt.xlabel('Epochs')
    plt.ylabel('Accuracy')
    plt.legend()

    plt.tight_layout()
    plt.show()


img_size = 50
size = 1000
batch_size = 15
num_epochs = 10

data, labels = gen_data(size, img_size)
(train_data, val_data, test_data), (train_labels,
                                    val_labels, test_labels) = data_preprocessing(data, labels)

model = Sequential([
    Input(shape=(img_size, img_size, 1)),
    Conv2D(8, (3, 3), padding='same', activation='relu'),
    MaxPooling2D((2, 2)),
    Conv2D(16, (3, 3), padding='same', activation='relu'),
    MaxPooling2D((2, 2)),
    Flatten(),
    Dense(128, activation='relu'),
    Dropout(0.5),
    Dense(1, activation='sigmoid')
])
# model.compile(loss='binary_crossentropy',
#               optimizer='adam',
#               metrics=[Precision(), Recall()])
model.compile(loss='binary_crossentropy',
              optimizer='adam',
              metrics=['accuracy'])
H = model.fit(train_data, train_labels,
              batch_size=batch_size, epochs=num_epochs,
              verbose=1, validation_data=(val_data, val_labels))
model.evaluate(test_data, test_labels, verbose=1)
model.save('cnn.h5')
model.summary()
draw_results(H)
