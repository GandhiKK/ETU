const gulp = require('gulp');
const less = require('gulp-less');
const babel = require('gulp-babel');
const babelCore = require('babel-core');
const pug = require('gulp-pug');
const del = require('del');


gulp.task('clean_js', function(){
    return del('./public/gulp_scripts/*.js');
});

gulp.task('make_js', function(){
    return gulp.src('./public/scripts/*.js')
        .pipe(babel())
        .pipe(gulp.dest('./public/gulp_scripts/'))
});

gulp.task('clean_css', function(){
    return del('./public/stylesheets/*.css');
});

gulp.task('make_css', function(){
    return gulp.src('./public/less/*.less')
        .pipe(less())
        .pipe(gulp.dest('./public/stylesheets/'))
});

gulp.task("default",gulp.parallel((gulp.series('clean_js', 'make_js')),(gulp.series('clean_css', 'make_css'))));