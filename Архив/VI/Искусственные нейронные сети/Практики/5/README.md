# Практика 5, вариант 4_3

## Задача

Необходимо в зависимости от варианта сгенерировать датасет и сохранить его в формате csv. Построить модель, которая будет содержать в себе автокодировщик и регрессионную модель.

Обучить модель и разбить обученную модель на 3: Модель кодирования данных (Входные данные -> Закодированные данные), модель декодирования данных (Закодированные данные -> Декодированные данные), и регрессионную модель (Входные данные -> Результат регрессии). В качестве результата представить исходный код, сгенерированные данные в формате csv, кодированные и декодированные данные в формате csv, результат регрессии в формате csv (что должно быть и что выдает модель), и сами 3 модели в формате h5.

### X ∈ N(0, 10); e ∈ N(0, 0.3)

### Цель регрессии: 3 признак

|Признак|1|2|*3*|4|5|6|7|
|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|
|**Формула**|cos(X)+e|-X+e|**sin(X)\*X+e**|sqrt(\|X\|)+e|X^2+e|-\|X\|+4|X-(X^2)/5+e|

## Генерация данных

Для генерации данных был написан модуль `gen_data.py`. Всего генерируется 500 строк данных: 400 для обучения и 100 для проверки.

```py
def gen_data(x, e, n):
    validation_split = 0.2
    train_size, test_size = np.around(
        [n*(1-validation_split), n*validation_split]).astype(int)

    x = np.random.normal(x[0], x[1], n)
    e = np.random.normal(e[0], e[1], n)
    gen_x = np.array([(np.cos(x)*x + e), (-x+e), (np.sqrt(abs(x))+e),
                      (x**2+e), (-abs(x)+4), (x-((x**2)/5)+e)]).transpose()
    gen_y = (np.sin(x)*x + e).reshape((-1, 1))

    train_x = gen_x[:train_size]
    train_y = gen_y[:train_size]
    test_x = gen_x[-test_size:]
    test_y = gen_y[-test_size:]
    return (train_x, train_y), (test_x, test_y), x


def solution():
    x = np.array([0, 10])
    e = np.array([0, 0.3])
    n = 500

    (train_data, train_targets), (test_data, test_targets), all_x = gen_data(x, e, n)

    np.savetxt('train_data.csv', train_data, delimiter=';')
    np.savetxt('train_targets.csv', train_targets, delimiter=';')
    np.savetxt('test_data.csv', test_data, delimiter=';')
    np.savetxt('test_targets.csv', test_targets, delimiter=';')

    all_y = np.vstack((train_data, test_data))
    all_p = np.vstack((train_targets, test_targets))
    drawResults(all_x, all_y, all_p)
```

* `train_data.csv` - признаки для обучения
* `train_targets.csv` - цель регрессии обучения
* `test_data.csv` - признаки для проверки
* `test_targets.csv` - цель регрессии проверки

Также выводятся графики сгенерированных данных для цели регрессии и признаков.

![Цель регрессии](Figure_1.png 'Цель регрессии')
![Признаки](Figure_2.png 'Признаки')

## Модель

Была построена модель в функциональном виде, которая содержит в себе автокодировщик и регрессионную модель.

```py
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
```

Модель имеет один вход и два выхода: результат регрессии и декодированные данные `model = Model(inputs=[input_data], outputs=[regression, decoded])`

Далее модель была обучена со следующими параметрами:

```py
model.compile(optimizer='adam', loss='mse', metrics=['mae'], loss_weights=[1., 0.5])
model.fit([train_data], [train_targets, train_data], epochs=200, batch_size=25, validation_data=([test_data], [test_targets, test_data]))
```

Далее модель была разбита на три. Модель кодирования данных (Входные данные -> Закодированные данные), модель декодирования данных (Закодированные данные -> Декодированные данные), и регрессионную модель (Входные данные -> Результат регрессии).

```py
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
```

Таже были выполнены запуски всех моделей на валидационных данных и сохранены полученные резульаты.

Сравнение предсказаний регрессии с верными значениями:

|Регрессия|Истина|
|:-----:|:-----:|
|3.294224023818969727e+00|3.124176196435995978e+00|
|6.859165430068969727e-01|6.327028432341148534e-01|
|-1.459997653961181641e+01|-1.064657469294270520e+01|
|1.432024955749511719e+00|1.360533239207029510e+00|
|-7.694729447364807129e+00|-7.388540997205320870e+00|
|7.656682491302490234e+00|8.056551657986950943e+00|
|-5.263125419616699219e+00|-4.831086483168626877e+00|
|6.098175644874572754e-01|6.059700014301826476e-01|
|1.577019095420837402e+00|1.615434703765252555e+00|

В конце было произведено сохранение моделей: `encoded.h5`, `decoded.h5`, `regression.h5`
