import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '1'
from tensorflow.keras.layers import Dense, Activation, Flatten
from tensorflow.keras.models import Sequential
from tensorflow.keras.utils import to_categorical
import tensorflow.keras.optimizers as opti
import tensorflow as tf
from keras.preprocessing.image import load_img
from keras.preprocessing.image import img_to_array
import numpy as np

mnist = tf.keras.datasets.mnist
(train_images, train_labels), (test_images, test_labels) = mnist.load_data()

train_images = train_images / 255.0
test_images = test_images / 255.0
train_labels = to_categorical(train_labels)
test_labels = to_categorical(test_labels)

model = Sequential()
model.add(Flatten())
model.add(Dense(256, activation='relu'))
model.add(Dense(10, activation='softmax'))


# optimus = opti.SGD(learning_rate=0.1, nesterov=True)
# optimus = opti.Adagrad(learning_rate=0.1)
# optimus = opti.RMSprop(learning_rate=0.001, rho=0.9)
# optimus = opti.Adadelta(learning_rate=1.0, rho=0.95)
# optimus = opti.Adam(learning_rate=0.001, beta_1=0.9, beta_2=0.999)
optimus = opti.Nadam(learning_rate=0.001, beta_1=0.9, beta_2=0.999)
# optimus = opti.Adamax(learning_rate=0.002, beta_1=0.9, beta_2=0.999)

model.compile(optimizer=optimus, loss='categorical_crossentropy',
              metrics=['accuracy'])
model.fit(train_images, train_labels, epochs=5, batch_size=128)

test_loss, test_acc = model.evaluate(test_images, test_labels)
print('test_loss: ', np.around(test_loss, decimals=5))
print('test_acc: {:.2%}'.format(test_acc))

def load_image(filename):
    img = load_img(filename, color_mode='grayscale', target_size=(28, 28))
    img = img_to_array(img)
    img = img.reshape(1, 28, 28, 1)
    img = img.astype('float32') / 255.0
    return img

def pred_img(model, filename):
    img = load_image(filename)
    digit = np.argmax(model.predict(img), axis=-1)
    print(digit[0])

while(True):
    print('type img name to pred; 0 to exit')
    filename = input()
    if filename != '0':
        pred_img(model, filename)
    else:
        break
