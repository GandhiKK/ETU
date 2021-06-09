import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '1'
from tensorflow.keras import models
from tensorflow.keras import layers
import matplotlib.colors as mclr
import matplotlib.pyplot as plt
import numpy as np
from keras_visualizer import visualizer


def genData(size=500):
    data = np.random.rand(size, 2)*2 - 1
    label = np.zeros([size, 1])
    for i, p in enumerate(data):
        if (p[0]+0.2)**2 + (0.6*p[1])**2 >= 0.25:
            label[i] = 0.
        else:
            label[i] = 1.
    div = round(size*0.8)
    train_data = data[:div, :]
    test_data = data[div:, :]
    train_label = label[:div, :]
    test_label = label[div:, :]
    return (train_data, train_label), (test_data, test_label)


def drawResults(data, label, prediction):
    p_label = np.array([round(x[0]) for x in prediction])
    plt.scatter(data[:, 0], data[:, 1], s=30, c=label[:, 0],
                cmap=mclr.ListedColormap(['red', 'blue']))
    plt.scatter(data[:, 0], data[:, 1], s=10, c=p_label,
                cmap=mclr.ListedColormap(['red', 'blue']))
    plt.grid()
    plt.show()


(train_data, train_label), (test_data, test_label) = genData()


# В данном месте необходимо создать модель и обучить ее
# print(train_data)
model = models.Sequential()
model.add(layers.Dense(48, activation='relu', input_shape=(2,)))
model.add(layers.Dense(16, activation='relu'))
model.add(layers.Dense(1, activation='sigmoid'))
visualizer(model, format='png', view=True)

model.compile(optimizer='rmsprop', loss='binary_crossentropy',
              metrics=['accuracy'])
H = model.fit(train_data, train_label, epochs=100, batch_size=20,
              validation_data=(test_data, test_label), verbose=2)


# Получение ошибки и точности в процессе обучения
loss = H.history['loss']
val_loss = H.history['val_loss']
acc = H.history['accuracy']
val_acc = H.history['val_accuracy']
epochs = range(1, len(loss) + 1)

# Построение графика ошибки
plt.plot(epochs, loss, 'bo', label='Training loss')
plt.plot(epochs, val_loss, 'b', label='Validation loss')
plt.title('Training and validation loss')
plt.xlabel('Epochs')
plt.ylabel('Loss')
plt.legend()
plt.show()

# Построение графика точности
plt.clf()
plt.plot(epochs, acc, 'bo', label='Training acc')
plt.plot(epochs, val_acc, 'b', label='Validation acc')
plt.title('Training and validation accuracy')
plt.xlabel('Epochs')
plt.ylabel('Accuracy')
plt.legend()
plt.show()

# Получение и вывод результатов на тестовом наборе
results = model.evaluate(test_data, test_label)
print(results)

# Вывод результатов бинарной классификации
all_data = np.vstack((train_data, test_data))
all_label = np.vstack((train_label, test_label))
pred = model.predict(all_data)
drawResults(all_data, all_label, pred)
