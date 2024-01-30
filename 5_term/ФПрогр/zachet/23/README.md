# Play framework

1) делаем в консоли ```sbt new playframework/play-scala-seed.g8``` создаем проект
2) переходим в папку проекта, делаем ```sbt run```, проект запустится на неком порте (у меня это 9000)
3) В папке <app_name>/app/views/index.html вставляем наш html-код
4) Заходим в папку conf/routes, где прописываются связи с коннекторами
и прописываем там ```GET / controllers.HomeController.index()```

По мере надобности добавляем новые routes в папку conf/routes, новые контроллеры в папку app/controllers и html-страницы в папку /app/views. 