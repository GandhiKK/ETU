"use strict";

$(document).ready(function () {
  start_config();
});

function start_config() {
  $('#id01').removeAttr("style").hide();
}

function edit_person(name, money, id) {
  $('#id01').show();
  $('input[name="redact_name"]').val(name);
  $('input[name="redact_money"]').val(money);
  $('form[name="pForm"]').attr('action', 'editPerson/' + id);
}