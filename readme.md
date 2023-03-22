Вариант #2\
Необходимо разработать программу, которая обрабатывает данные онлайн сервиса IMDB.\
Датасеты можно скачать на официальном сайте IMDB https://datasets.imdbws.com/\
Описание датасетов находится по ссылке https://www.imdb.com/interfaces/\
Каждый файл представляет из себя сжатый TSV файл, где данные располагаются в строчках, а поля разделены символом табуляции \t

Скачать датасет по ссылке можно с помощью команды wget, например

wget https://datasets.imdbws.com/title.basics.tsv.gz

Полученные файлы нужно распаковать

gunzip title.basics.tsv.gz

Программа должна принимать необходимые для работы имена распакованных файлов в качестве аргументов командной строки и выводить данные в стандартный вывод.\
Программа не должна брать в расчет фильмы для взрослых, и , если в варианте используется рейтинг, не должна учитывать рейтинг фильмов с числом оценок меньше 1000.\
Программа не должна использовать интерактивный ввод с клавиатуры, например, "введите имя файла", "введите необходимый год", "ведите q чтобы выйти" - такими программами не удобно пользоваться и их разработка занимает больше времени.

Ваш вариант:\
Вывести русские названия (при наличии) всех фильмов, которые снял режиссер, имя которого переданно в аргументах командной строки
