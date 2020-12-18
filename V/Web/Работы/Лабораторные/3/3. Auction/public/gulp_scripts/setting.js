"use strict";

$(document).ready(function () {
  start_config();
});

function start_config() {
  $('input[name="dt"]').removeAttr("style").hide();
  $('input[name="tm"]').removeAttr("style").hide();
  $('input[name="tmout"]').removeAttr("style").hide();
  $('input[name="tmtorg"]').removeAttr("style").hide();
  $('input[name="tminfo"]').removeAttr("style").hide();
  $('#ok').removeAttr("style").hide();
}

function edit_setting(dt, tm, tmout, tmtorg, tminfo) {
  $('#edit').removeAttr("style").hide();
  $('#dt').removeAttr("style").hide();
  $('#tm').removeAttr("style").hide();
  $('#tmout').removeAttr("style").hide();
  $('#tmtorg').removeAttr("style").hide();
  $('#tminfo').removeAttr("style").hide();
  $('#ok').show();
  $('input[name="dt"]').val(dt).show();
  $('input[name="tm"]').val(tm).show();
  $('input[name="tmout"]').val(tmout).show();
  $('input[name="tmtorg"]').val(tmtorg).show();
  $('input[name="tminfo"]').val(tminfo).show();
}