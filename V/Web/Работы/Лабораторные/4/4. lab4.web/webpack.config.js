module.exports = {
    entry: {
      enter: './public/assets/js/enter.js',
      admin: './public/assets/js/admin.js',
      user: './public/assets/js/user.js'
    },
    output: {
        filename: './js/[name].js'
    }
};