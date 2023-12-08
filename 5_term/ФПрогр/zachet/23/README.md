# Play framework

1) Скачиваем Play https://www.playframework.com/
2) Создаем проект через консоль: ```play new myApp2```
3) Запускаем браузер
4) В папке myApp2/app/views/index.html вставляем наш html-код
5) Заходим в папку conf/routes, где прописываются связи с коннекторами
и прописываем там ```GET / controllers.HomeController.index()```
6) В папке myApp2/app/controllers создаем файл HomeController.jawa
7) Открываем окно браузера