import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'
os.environ['TF_FORCE_GPU_ALLOW_GROWTH'] = 'true'
from sklearn.preprocessing import LabelEncoder
from matplotlib import gridspec
import matplotlib.pyplot as plt
from tensorflow.keras.layers import Dense
from tensorflow.keras.models import Sequential, Model
import numpy as np
from keras.layers import Input, Conv2D, MaxPooling2D, Dense, Dropout, Flatten
from keras.metrics import Precision, Recall
from keras.callbacks import TensorBoard, Callback


class KernelsCallback(Callback):
    def __init__(self, eps):
        self.eps = eps
        self.lays = [] 
                
    def set_model(self, model):    
        self.model = model  
        for i in range(len(model.layers)):
            if 'conv' in model.layers[i].name:
                self.lays.append(i)
        
    def on_epoch_end(self, epoch, logs=None):
        for layer in self.lays:        
            if epoch in self.eps:
                filters, biases = model.layers[layer].get_weights()
                
                f_min, f_max = filters.min(), filters.max()
                filters = (filters - f_min) / (f_max - f_min)
                
                out_channels = filters.shape[3]
                in_channels = filters.shape[2]
                
                for i in range(out_channels):
                    f = filters[:,:,:,i]    
                    ind = 1
                    for j in range(in_channels):
                        flt = plt.subplot(1, in_channels, ind)
                        flt.set_xticks([])
                        flt.set_yticks([])
                        plt.imshow(f[:,:,j], cmap='gray')
                        plt.savefig(f'imgs/{layer+1}_{i+1}_{epoch+1}.png')                    
                        ind += 1  
                    plt.clf()    
                    # <слой>_<фильтр>_<эпоха>


def gen_rect(SIZE=50):
    img = np.zeros([SIZE, SIZE])
    x = np.random.randint(0, SIZE)
    y = np.random.randint(0, SIZE)
    w = np.random.randint(SIZE // 10, SIZE // 2)
    h = np.random.randint(SIZE // 10, SIZE // 2)
    img[x:x + w, y:y + h] = 1
    return img


def gen_circle(SIZE=50):
    img = np.zeros([SIZE, SIZE])
    x = np.random.randint(0, SIZE)
    y = np.random.randint(0, SIZE)
    r = np.random.randint(SIZE // 10, SIZE // 3)
    for i in range(0, SIZE):
        for j in range(0, SIZE):
            if (i-x)**2 + (j-y)**2 <= r**2:
                img[i, j] = 1
    return img


def gen_data(SIZE=500, IMG_SIZE=50):
    c1 = SIZE // 2
    c2 = SIZE - c1
    label_c1 = np.full([c1, 1], 'Square')
    data_c1 = np.array([gen_rect(IMG_SIZE) for i in range(c1)])
    label_c2 = np.full([c2, 1], 'Circle')
    data_c2 = np.array([gen_circle(IMG_SIZE) for i in range(c2)])
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


IMG_SIZE = 50
SIZE = 1000
BATCH_SIZE = 15
NUM_EPOCHS = 10

FILTERS_EPOCHS = [0,5,9]

data, labels = gen_data(SIZE, IMG_SIZE)
(train_data, val_data, test_data), (train_labels,
                                    val_labels, test_labels) = data_preprocessing(data, labels)

model = Sequential([
    Input(shape=(IMG_SIZE, IMG_SIZE, 1)),
    Conv2D(8, (3, 3), padding='same', activation='relu'),
    MaxPooling2D((2, 2)),
    Conv2D(16, (3, 3), padding='same', activation='relu'),
    MaxPooling2D((2, 2)),
    Flatten(),
    Dense(128, activation='relu'),
    Dropout(0.5),
    Dense(1, activation='sigmoid')
])
model.compile(loss='binary_crossentropy',
              optimizer='adam',
              metrics=['accuracy'])
H = model.fit(train_data, train_labels,
              batch_size=BATCH_SIZE, epochs=NUM_EPOCHS,
              verbose=2, validation_data=(val_data, val_labels), callbacks=[KernelsCallback(FILTERS_EPOCHS)])
model.evaluate(test_data, test_labels, verbose=1)
# draw_results(H)
