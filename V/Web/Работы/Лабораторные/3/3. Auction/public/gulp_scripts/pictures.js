"use strict";

$(document).ready(function () {
    start_config();
});

function start_config() {
    $('#id02').removeAttr("style").hide();
}

function edit_picture(name, artist, price, min, max, id) {
    $('#id02').show();
    $('input[name="redact_name"]').val(name);
    $('input[name="redact_artist"]').val(artist);
    $('input[name="redact_price"]').val(price);
    $('input[name="redact_min"]').val(min);
    $('input[name="redact_max"]').val(max);
    $('form[name="postForm"]').attr('action', 'editPicture/' + id);
}

function new_picture() {
    let min = parseInt(document.getElementById("min").value)
    let max = parseInt(document.getElementById("max").value)

    // console.log(min)
    // console.log(max)


    let ans = min <= max;

    if (ans === false) alert("Минимальное не может быть больше максимального!")
    return ans
}