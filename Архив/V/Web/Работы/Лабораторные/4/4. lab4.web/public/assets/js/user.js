$(function () {
    $("#info-draggable").draggable({cursor: "move"});

    $("#slider").slider({
        create: function () {},
        slide: (event, ui) => {
            $(".price-offer").text(`Повысить цену на: ${ui.value}`);
        },
    });

    let socket = io.connect("http://localhost:3030");
    let pause;
    let lastIdArt = '0';
    let timeUpdateInterval;
    let isChangePrice = false;
    let finalCountDown;
    let countInterval;

    socket.on('connect', function () {
        let name = $('#name').text();

        socket.json.emit('join', {
            'name': name,
        });
    });

    socket.on('msg', function (msg) {
        appendMessage(msg);
    });

    socket.on('start', (msg) => {
        new Promise((resolve, reject) => {
            pause = parseInt(msg.pause);
            setTimeout(() => {
                send('endPause', 'next art');
            }, pause);
        }).then();

        appendMessage(msg);

        $.get(`/next/art/${lastIdArt}`)
            .done((resData) => {
                let slider = $("#slider");

                $('.art-block__image').attr('src', resData.src).show();
                $('.plug-square').removeClass('d-flex').hide();

                $(".art-block__name").text(`${resData.author} - ${resData.name}`);
                $(".art-block__price").text(resData.price);

                slider.slider({
                    max: parseInt(resData.maxStep),
                    min: parseInt(resData.minStep)
                });

                $(".price-offer").text(`Повысить цену на: ${slider.slider('value')}`);
                beginTimeMarket = new Date();
                timeUpdateInterval = setInterval(setTime, 1000);
                lastIdArt = resData.id;
            }
        );
    });

    socket.on('market', (msg) => {
        isChangePrice = true;
        appendMessage(msg);
    });

    socket.on('endMarket', (msg) => {
        new Promise((resolve, reject) => {
            appendMessage(msg);
            isChangePrice = false;
        }).then();

        clearInterval(finalCountDown);

        if(lastIdArt != $("#count").text()) {
            new Promise((resolve, reject) => {
                setTimeout(() => {send('endPause', 'next art')}, pause);
            }).then();
            //setTimeout(() => {send("endPause", "next art");}, pause);
            $.get(`/next/art/${lastIdArt}`).done((resData) => {
                new Promise((resolve, reject) => {
                    $('.art-block__image').attr('src', resData.src);
                    $(".art-block__name").text(`${resData.author} - ${resData.name}`);
                    $(".art-block__price").text(resData.price);

                    $("#slider").slider({
                        max: parseInt(resData.maxStep),
                        min: parseInt(resData.minStep)
                    });

                    $(".price-offer").text(`Повысить цену на: ${$("#slider").slider("value")}`);

                    lastIdArt = resData.id;
                }).then();
            });
        } else {
            clearInterval(timeUpdateInterval);
            send('endAuction', 'end');

            $('.art-block__image').hide();
            $('.plug-square').addClass('d-flex').text('Аукцион закончен').show();

            $(".art-block__name").text('');
            $(".art-block__price").text('');
        }
    });

    socket.on('price.new', (msg) => {
        appendMessage(msg);
        $(".art-block__price").text(parseInt($(".art-block__price").text()) + parseInt(msg.up));
    });

    socket.on('win', (msg) => {
        new Promise((resolve, reject) => {
            let div = document.createElement("div");
            div.innerHTML = `${$(".art-block__name").text()} ${$(".art-block__price").text()}`;
            purchases.appendChild(div);
            $("#money").text(parseInt($("#money").text()) - parseInt($(".art-block__price").text()));
            socket.json.emit('toAdmin', {
                "name": $("#name").text(),
                "money":  $("#money").text(),
                "art": $(".art-block__name").text()
            });
        }).then();
    });

    socket.on('END', (msg) => {
        appendMessage(msg);
    });

    /**
     *
     */
    $(".price-offer-button").click(() => {
        let slider = $("#slider");

        if(isChangePrice) {
            if(parseInt($("#money").text()) - parseInt($(".art-block__price").text()) - parseInt(slider.slider('value')) < 0) {
                window.alert('Недостаточно средств!');
                return;
            }

            socket.json.emit('price.offer', {
                "name": $("#name").text(),
                "up": slider.slider("value")
            });
        }
    });

    /**
     * Отправить событие
     *
     * @param type
     * @param value
     */
    function send(type, value) {
        if(socket) {
            socket.json.emit(type, {"value": value});
        }
    }

    /**
     * Обновить таймер
     */
    function setTime() {
        let delta = new Date() - beginTimeMarket;
        let seconds = Math.round(delta / 1000);
        let minutes = 0;

        if(seconds > 60) {
            minutes = Math.floor(seconds/60);
            seconds = seconds % 60;
        }

        if (minutes < 10) {
            minutes = '0' + String(minutes);
        }

        if (seconds < 10) {
            seconds = '0' + String(seconds);
        }

        $("#time").text(`${minutes}:${seconds}`);
    }

    /**
     * Отправить сообщение в информационный чат
     *
     * @param socketMessage
     * @param color
     */

    function appendMessage(socketMessage, color = 'black') {
        new Promise((resolve, reject) => {
            console.log(`${new Date().toLocaleTimeString()}: ${color} ${socketMessage.message} ${socketMessage.time}`);
        }).then();

        let div = document.createElement("div");
        div.style.color = color;
        div.innerHTML = `<span class="info-message__time">${new Date(socketMessage.time).toLocaleTimeString()}</span> ${socketMessage.message}`;
        $('#info-messages .content').append(div);
    }
});
