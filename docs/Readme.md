Язык программирования РефалАБ (RefalAB) является
диалектом языка [Рефал-2](http://www.refal.net/~belous/refal2-r.htm).

Данное руководство основанно на работе [[1](R_5.md#%D0%BF%D1%80%D0%B8%D0%BB%D0%BE%D0%B6%D0%B5%D0%BD%D0%B8%D0%B5-%D0%B4)].

Содержание
-------------------------------------

[1. Описание языка](R_1.md#1-%D0%BE%D0%BF%D0%B8%D1%81%D0%B0%D0%BD%D0%B8%D0%B5-%D1%8F%D0%B7%D1%8B%D0%BA%D0%B0)
- [Введение](R_1.md#%D0%B2%D0%B2%D0%B5%D0%B4%D0%B5%D0%BD%D0%B8%D0%B5)
- [1.1. Назначение языка](R_1.md#11-%D0%BD%D0%B0%D0%B7%D0%BD%D0%B0%D1%87%D0%B5%D0%BD%D0%B8%D0%B5-%D1%8F%D0%B7%D1%8B%D0%BA%D0%B0)
- [1.2. Обрабатываемые данные](R_1.md#12-%D0%BE%D0%B1%D1%80%D0%B0%D0%B1%D0%B0%D1%82%D1%8B%D0%B2%D0%B0%D0%B5%D0%BC%D1%8B%D0%B5-%D0%B4%D0%B0%D0%BD%D0%BD%D1%8B%D0%B5)
- [1.3. Функции](R_1.md#13-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%B8)
- [1.4. Переменные](R_1.md#14-%D0%BF%D0%B5%D1%80%D0%B5%D0%BC%D0%B5%D0%BD%D0%BD%D1%8B%D0%B5)
- [1.5. Рекурсивные функции](R_1.md#15-%D1%80%D0%B5%D0%BA%D1%83%D1%80%D1%81%D0%B8%D0%B2%D0%BD%D1%8B%D0%B5-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%B8)
- [1.6. Снятие неоднозначности при отождествлении](R_1.md#16-%D1%81%D0%BD%D1%8F%D1%82%D0%B8%D0%B5-%D0%BD%D0%B5%D0%BE%D0%B4%D0%BD%D0%BE%D0%B7%D0%BD%D0%B0%D1%87%D0%BD%D0%BE%D1%81%D1%82%D0%B8-%D0%BF%D1%80%D0%B8-%D0%BE%D1%82%D0%BE%D0%B6%D0%B4%D0%B5%D1%81%D1%82%D0%B2%D0%BB%D0%B5%D0%BD%D0%B8%D0%B8)
- [1.7. Спецификаторы переменных](R_1.md#17-%D1%81%D0%BF%D0%B5%D1%86%D0%B8%D1%84%D0%B8%D0%BA%D0%B0%D1%82%D0%BE%D1%80%D1%8B-%D0%BF%D0%B5%D1%80%D0%B5%D0%BC%D0%B5%D0%BD%D0%BD%D1%8B%D1%85)
- [1.8. Общая структура программы](R_1.md#18-%D0%BE%D0%B1%D1%89%D0%B0%D1%8F-%D1%81%D1%82%D1%80%D1%83%D0%BA%D1%82%D1%83%D1%80%D0%B0-%D0%BF%D1%80%D0%BE%D0%B3%D1%80%D0%B0%D0%BC%D0%BC%D1%8B)
- [1.9. Пустые функции](R_1.md#19-%D0%BF%D1%83%D1%81%D1%82%D1%8B%D0%B5-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%B8)
- [1.10. Эквивалентные имена](R_1.md#110-%D1%8D%D0%BA%D0%B2%D0%B8%D0%B2%D0%B0%D0%BB%D0%B5%D0%BD%D1%82%D0%BD%D1%8B%D0%B5-%D0%B8%D0%BC%D0%B5%D0%BD%D0%B0)
- [1.11. Модули](R_1.md#111-%D0%BC%D0%BE%D0%B4%D1%83%D0%BB%D0%B8)
- [1.12. Первичные функции](R_1.md#112-%D0%BF%D0%B5%D1%80%D0%B2%D0%B8%D1%87%D0%BD%D1%8B%D0%B5-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%B8)
- [1.13. Копилка](R_1.md#113-%D0%BA%D0%BE%D0%BF%D0%B8%D0%BB%D0%BA%D0%B0)
- [1.14. Статические и динамические ящики](R_1.md#114-%D1%81%D1%82%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D0%B8-%D0%B4%D0%B8%D0%BD%D0%B0%D0%BC%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5-%D1%8F%D1%89%D0%B8%D0%BA%D0%B8)

[2. Описание библиотеки](R_2.md#2-%D0%BE%D0%BF%D0%B8%D1%81%D0%B0%D0%BD%D0%B8%D0%B5-%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA%D0%B8)
- [Введение](R_2.md#%D0%B2%D0%B2%D0%B5%D0%B4%D0%B5%D0%BD%D0%B8%D0%B5)
- [2.1. Функции ввода-вывода](R_2.md#21-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%B8-%D0%B2%D0%B2%D0%BE%D0%B4%D0%B0-%D0%B2%D1%8B%D0%B2%D0%BE%D0%B4%D0%B0)
- [2.2. Функции арифметики](R_2.md#22-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%B8-%D0%B0%D1%80%D0%B8%D1%84%D0%BC%D0%B5%D1%82%D0%B8%D0%BA%D0%B8)
- [2.3. Функции и спецификаторы лексического анализа](R_2.md#23-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%B8-%D0%B8-%D1%81%D0%BF%D0%B5%D1%86%D0%B8%D1%84%D0%B8%D0%BA%D0%B0%D1%82%D0%BE%D1%80%D1%8B-%D0%BB%D0%B5%D0%BA%D1%81%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%BE%D0%B3%D0%BE-%D0%B0%D0%BD%D0%B0%D0%BB%D0%B8%D0%B7%D0%B0)
- [2.4. Функции для работы с символьными файлами](R_2.md#24-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%B8-%D0%B4%D0%BB%D1%8F-%D1%80%D0%B0%D0%B1%D0%BE%D1%82%D1%8B-%D1%81-%D1%81%D0%B8%D0%BC%D0%B2%D0%BE%D0%BB%D1%8C%D0%BD%D1%8B%D0%BC%D0%B8-%D1%84%D0%B0%D0%B9%D0%BB%D0%B0%D0%BC%D0%B8)
- [2.5. Функция порождения процесса](R_2.md#25-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D1%8F-%D0%BF%D0%BE%D1%80%D0%BE%D0%B6%D0%B4%D0%B5%D0%BD%D0%B8%D1%8F-%D0%BF%D1%80%D0%BE%D1%86%D0%B5%D1%81%D1%81%D0%B0)
- [2.6. Функции для работы с символами-метками](R_2.md#26-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%B8-%D0%B4%D0%BB%D1%8F-%D1%80%D0%B0%D0%B1%D0%BE%D1%82%D1%8B-%D1%81-%D1%81%D0%B8%D0%BC%D0%B2%D0%BE%D0%BB%D0%B0%D0%BC%D0%B8-%D0%BC%D0%B5%D1%82%D0%BA%D0%B0%D0%BC%D0%B8)
- [2.7. Функции для работы с копилкой](R_2.md#27-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%B8-%D0%B4%D0%BB%D1%8F-%D1%80%D0%B0%D0%B1%D0%BE%D1%82%D1%8B-%D1%81-%D0%BA%D0%BE%D0%BF%D0%B8%D0%BB%D0%BA%D0%BE%D0%B9)
- [2.8. Функции для работы со статическими и динамическими ящиками](R_2.md#28-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%B8-%D0%B4%D0%BB%D1%8F-%D1%80%D0%B0%D0%B1%D0%BE%D1%82%D1%8B-%D1%81%D0%BE-%D1%81%D1%82%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%BC%D0%B8-%D0%B8-%D0%B4%D0%B8%D0%BD%D0%B0%D0%BC%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%BC%D0%B8-%D1%8F%D1%89%D0%B8%D0%BA%D0%B0%D0%BC%D0%B8)
- [2.9. Функции для работы со временем](R_2.md#29-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%B8-%D0%B4%D0%BB%D1%8F-%D1%80%D0%B0%D0%B1%D0%BE%D1%82%D1%8B-%D1%81%D0%BE-%D0%B2%D1%80%D0%B5%D0%BC%D0%B5%D0%BD%D0%B5%D0%BC)
- [2.10. Функция удаления функциональных термов в поле зрения](R_2.md#210-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D1%8F-%D1%83%D0%B4%D0%B0%D0%BB%D0%B5%D0%BD%D0%B8%D1%8F-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%BE%D0%BD%D0%B0%D0%BB%D1%8C%D0%BD%D1%8B%D1%85-%D1%82%D0%B5%D1%80%D0%BC%D0%BE%D0%B2-%D0%B2-%D0%BF%D0%BE%D0%BB%D0%B5-%D0%B7%D1%80%D0%B5%D0%BD%D0%B8%D1%8F)
- [2.11. Функции высшего порядка](R_2.md#211-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%B8-%D0%B2%D1%8B%D1%81%D1%88%D0%B5%D0%B3%D0%BE-%D0%BF%D0%BE%D1%80%D1%8F%D0%B4%D0%BA%D0%B0)
- [2.12. Функции и спецификаторы, специфичные для сред Windows и POSIX](R_2.md#212-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%B8-%D0%B8-%D1%81%D0%BF%D0%B5%D1%86%D0%B8%D1%84%D0%B8%D0%BA%D0%B0%D1%82%D0%BE%D1%80%D1%8B-%D1%81%D0%BF%D0%B5%D1%86%D0%B8%D1%84%D0%B8%D1%87%D0%BD%D1%8B%D0%B5-%D0%B4%D0%BB%D1%8F-%D1%81%D1%80%D0%B5%D0%B4-windows-%D0%B8-posix)
- [2.13. Системные функции](R_2.md#213-%D1%81%D0%B8%D1%81%D1%82%D0%B5%D0%BC%D0%BD%D1%8B%D0%B5-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%B8)
- [2.14. Функции для работы со случайными числами](R_2.md#214-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%B8-%D0%B4%D0%BB%D1%8F-%D1%80%D0%B0%D0%B1%D0%BE%D1%82%D1%8B-%D1%81%D0%BE-%D1%81%D0%BB%D1%83%D1%87%D0%B0%D0%B9%D0%BD%D1%8B%D0%BC%D0%B8-%D1%87%D0%B8%D1%81%D0%BB%D0%B0%D0%BC%D0%B8)
- [2.15. Пустые функции](R_2.md#215-%D0%BF%D1%83%D1%81%D1%82%D1%8B%D0%B5-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%B8)
- [2.16. Описание функций](R_2.md#216-%D0%BE%D0%BF%D0%B8%D1%81%D0%B0%D0%BD%D0%B8%D0%B5-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%B9)
- [2.17. Описание пустых функций](R_2.md#217-%D0%BE%D0%BF%D0%B8%D1%81%D0%B0%D0%BD%D0%B8%D0%B5-%D0%BF%D1%83%D1%81%D1%82%D1%8B%D1%85-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%B9)
- [2.18. Описание спецификаторов](R_2.md#218-%D0%BE%D0%BF%D0%B8%D1%81%D0%B0%D0%BD%D0%B8%D0%B5-%D1%81%D0%BF%D0%B5%D1%86%D0%B8%D1%84%D0%B8%D0%BA%D0%B0%D1%82%D0%BE%D1%80%D0%BE%D0%B2)

[3. Интерфейс РефалАБ и Си](R_3.md#3-%D0%B8%D0%BD%D1%82%D0%B5%D1%80%D1%84%D0%B5%D0%B9%D1%81-%D1%80%D0%B5%D1%84%D0%B0%D0%BB%D0%B0%D0%B1-%D0%B8-%D1%81%D0%B8)
- [Введение](R_3.md#%D0%B2%D0%B2%D0%B5%D0%B4%D0%B5%D0%BD%D0%B8%D0%B5)
- [3.1. Обработка ошибок](R_3.md#31-%D0%BE%D0%B1%D1%80%D0%B0%D0%B1%D0%BE%D1%82%D0%BA%D0%B0-%D0%BE%D1%88%D0%B8%D0%B1%D0%BE%D0%BA)
- [3.2. Представление выражений в памяти машины](R_3.md#32-%D0%BF%D1%80%D0%B5%D0%B4%D1%81%D1%82%D0%B0%D0%B2%D0%BB%D0%B5%D0%BD%D0%B8%D0%B5-%D0%B2%D1%8B%D1%80%D0%B0%D0%B6%D0%B5%D0%BD%D0%B8%D0%B9-%D0%B2-%D0%BF%D0%B0%D0%BC%D1%8F%D1%82%D0%B8-%D0%BC%D0%B0%D1%88%D0%B8%D0%BD%D1%8B)
- [3.3. Доступ к полям звена из программы на Си](R_3.md#33-%D0%B4%D0%BE%D1%81%D1%82%D1%83%D0%BF-%D0%BA-%D0%BF%D0%BE%D0%BB%D1%8F%D0%BC-%D0%B7%D0%B2%D0%B5%D0%BD%D0%B0-%D0%B8%D0%B7-%D0%BF%D1%80%D0%BE%D0%B3%D1%80%D0%B0%D0%BC%D0%BC%D1%8B-%D0%BD%D0%B0-%D1%81%D0%B8)
- [3.4. Представление функциональных скобок в списковой памяти](R_3.md#34-%D0%BF%D1%80%D0%B5%D0%B4%D1%81%D1%82%D0%B0%D0%B2%D0%BB%D0%B5%D0%BD%D0%B8%D0%B5-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%BE%D0%BD%D0%B0%D0%BB%D1%8C%D0%BD%D1%8B%D1%85-%D1%81%D0%BA%D0%BE%D0%B1%D0%BE%D0%BA-%D0%B2-%D1%81%D0%BF%D0%B8%D1%81%D0%BA%D0%BE%D0%B2%D0%BE%D0%B9-%D0%BF%D0%B0%D0%BC%D1%8F%D1%82%D0%B8)
- [3.5. Представоение ящиков в списковой памяти](R_3.md#35-%D0%BF%D1%80%D0%B5%D0%B4%D1%81%D1%82%D0%B0%D0%B2%D0%BB%D0%B5%D0%BD%D0%B8%D0%B5-%D1%8F%D1%89%D0%B8%D0%BA%D0%BE%D0%B2-%D0%B2-%D1%81%D0%BF%D0%B8%D1%81%D0%BA%D0%BE%D0%B2%D0%BE%D0%B9-%D0%BF%D0%B0%D0%BC%D1%8F%D1%82%D0%B8)
- [3.6. Печать выражений](R_3.md#36-%D0%BF%D0%B5%D1%87%D0%B0%D1%82%D1%8C-%D0%B2%D1%8B%D1%80%D0%B0%D0%B6%D0%B5%D0%BD%D0%B8%D0%B9)
- [3.7. Процессы](R_3.md#37-%D0%BF%D1%80%D0%BE%D1%86%D0%B5%D1%81%D1%81%D1%8B)
- [3.8. Общий блок refal](R_3.md#38-%D0%BE%D0%B1%D1%89%D0%B8%D0%B9-%D0%B1%D0%BB%D0%BE%D0%BA-refal)
- [3.9. Инициализация РефалАБ-машины](R_3.md#39-%D0%B8%D0%BD%D0%B8%D1%86%D0%B8%D0%B0%D0%BB%D0%B8%D0%B7%D0%B0%D1%86%D0%B8%D1%8F-%D1%80%D0%B5%D1%84%D0%B0%D0%BB%D0%B0%D0%B1-%D0%BC%D0%B0%D1%88%D0%B8%D0%BD%D1%8B)
- [3.10. Пространство списковой памяти и список свободных звеньев](R_3.md#310-%D0%BF%D1%80%D0%BE%D1%81%D1%82%D1%80%D0%B0%D0%BD%D1%81%D1%82%D0%B2%D0%BE-%D1%81%D0%BF%D0%B8%D1%81%D0%BA%D0%BE%D0%B2%D0%BE%D0%B9-%D0%BF%D0%B0%D0%BC%D1%8F%D1%82%D0%B8-%D0%B8-%D1%81%D0%BF%D0%B8%D1%81%D0%BE%D0%BA-%D1%81%D0%B2%D0%BE%D0%B1%D0%BE%D0%B4%D0%BD%D1%8B%D1%85-%D0%B7%D0%B2%D0%B5%D0%BD%D1%8C%D0%B5%D0%B2)
- [3.11. Таблица состояния процесса](R_3.md#311-%D1%82%D0%B0%D0%B1%D0%BB%D0%B8%D1%86%D0%B0-%D1%81%D0%BE%D1%81%D1%82%D0%BE%D1%8F%D0%BD%D0%B8%D1%8F-%D0%BF%D1%80%D0%BE%D1%86%D0%B5%D1%81%D1%81%D0%B0)
- [3.12. Создание и уничтожение процессов](R_3.md#312-%D1%81%D0%BE%D0%B7%D0%B4%D0%B0%D0%BD%D0%B8%D0%B5-%D0%B8-%D1%83%D0%BD%D0%B8%D1%87%D1%82%D0%BE%D0%B6%D0%B5%D0%BD%D0%B8%D0%B5-%D0%BF%D1%80%D0%BE%D1%86%D0%B5%D1%81%D1%81%D0%BE%D0%B2)
- [3.13. Запуск процессов](R_3.md#313-%D0%B7%D0%B0%D0%BF%D1%83%D1%81%D0%BA-%D0%BF%D1%80%D0%BE%D1%86%D0%B5%D1%81%D1%81%D0%BE%D0%B2)
- [3.14. Примеры управления процессами](R_3.md#314-%D0%BF%D1%80%D0%B8%D0%BC%D0%B5%D1%80%D1%8B-%D1%83%D0%BF%D1%80%D0%B0%D0%B2%D0%BB%D0%B5%D0%BD%D0%B8%D1%8F-%D0%BF%D1%80%D0%BE%D1%86%D0%B5%D1%81%D1%81%D0%B0%D0%BC%D0%B8)
- [3.15. Сборка мусора](R_3.md#315-%D1%81%D0%B1%D0%BE%D1%80%D0%BA%D0%B0-%D0%BC%D1%83%D1%81%D0%BE%D1%80%D0%B0)
- [3.16. Динамический захват списковой памяти](R_3.md#316-%D0%B4%D0%B8%D0%BD%D0%B0%D0%BC%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B9-%D0%B7%D0%B0%D1%85%D0%B2%D0%B0%D1%82-%D1%81%D0%BF%D0%B8%D1%81%D0%BA%D0%BE%D0%B2%D0%BE%D0%B9-%D0%BF%D0%B0%D0%BC%D1%8F%D1%82%D0%B8)
- [3.17. Вызов программы на Си из РефалАБ-программы](R_3.md#317-%D0%B2%D1%8B%D0%B7%D0%BE%D0%B2-%D0%BF%D1%80%D0%BE%D0%B3%D1%80%D0%B0%D0%BC%D0%BC%D1%8B-%D0%BD%D0%B0-%D1%81%D0%B8-%D0%B8%D0%B7%D1%80%D0%B5%D1%84%D0%B0%D0%BB%D0%B0%D0%B1-%D0%BF%D1%80%D0%BE%D0%B3%D1%80%D0%B0%D0%BC%D0%BC%D1%8B)
- [3.18. Написание первичных функций на Си](R_3.md#318-%D0%BD%D0%B0%D0%BF%D0%B8%D1%81%D0%B0%D0%BD%D0%B8%D0%B5-%D0%BF%D0%B5%D1%80%D0%B2%D0%B8%D1%87%D0%BD%D1%8B%D1%85-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%B9-%D0%BD%D0%B0-%D1%81%D0%B8)
- [3.19. Примеры первичных функций на Си](R_3.md#319-%D0%BF%D1%80%D0%B8%D0%BC%D0%B5%D1%80%D1%8B-%D0%BF%D0%B5%D1%80%D0%B2%D0%B8%D1%87%D0%BD%D1%8B%D1%85-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%B9-%D0%BD%D0%B0-%D1%81%D0%B8)

[4. Компиляция и исполнение РефалАБ-программ](R_4.md#4-%D0%BA%D0%BE%D0%BC%D0%BF%D0%B8%D0%BB%D1%8F%D1%86%D0%B8%D1%8F-%D0%B8-%D0%B8%D1%81%D0%BF%D0%BE%D0%BB%D0%BD%D0%B5%D0%BD%D0%B8%D0%B5-%D1%80%D0%B5%D1%84%D0%B0%D0%BB%D0%B0%D0%B1-%D0%BF%D1%80%D0%BE%D0%B3%D1%80%D0%B0%D0%BC%D0%BC)
- [Введение](https://github.com/Aleksandr3Bocharov/RefalAB/blob/main/docs/R_4.md#%D0%B2%D0%B2%D0%B5%D0%B4%D0%B5%D0%BD%D0%B8%D0%B5)
- [4.1. Сборка РефалАБ-системы](R_4.md#41-%D1%81%D0%B1%D0%BE%D1%80%D0%BA%D0%B0-%D1%80%D0%B5%D1%84%D0%B0%D0%BB%D0%B0%D0%B1-%D1%81%D0%B8%D1%81%D1%82%D0%B5%D0%BC%D1%8B)
  - [4.1.1. Windows](R_4.md#411-windows)
  - [4.1.2. POSIX](R_4.md#412-posix)
- [4.2. РефалАБ-система на ПК](R_4.md#42-%D1%80%D0%B5%D1%84%D0%B0%D0%BB%D0%B0%D0%B1-%D1%81%D0%B8%D1%81%D1%82%D0%B5%D0%BC%D0%B0-%D0%BD%D0%B0-%D0%BF%D0%BA)
  - [4.2.1. Windows](R_4.md#421-windows)
  - [4.2.2. POSIX](R_4.md#422-posix)
- [4.3. Подготовка исходных текстов РефалАБ-программ](R_4.md#43-%D0%BF%D0%BE%D0%B4%D0%B3%D0%BE%D1%82%D0%BE%D0%B2%D0%BA%D0%B0-%D0%B8%D1%81%D1%85%D0%BE%D0%B4%D0%BD%D1%8B%D1%85-%D1%82%D0%B5%D0%BA%D1%81%D1%82%D0%BE%D0%B2%D1%80%D0%B5%D1%84%D0%B0%D0%BB%D0%B0%D0%B1-%D0%BF%D1%80%D0%BE%D0%B3%D1%80%D0%B0%D0%BC%D0%BC)
- [4.4. Компиляция РефалАБ-модулей](R_4.md#44-%D0%BA%D0%BE%D0%BC%D0%BF%D0%B8%D0%BB%D1%8F%D1%86%D0%B8%D1%8F-%D1%80%D0%B5%D1%84%D0%B0%D0%BB%D0%B0%D0%B1-%D0%BC%D0%BE%D0%B4%D1%83%D0%BB%D0%B5%D0%B9)
- [4.5. Компиляция модулей первичных функций](R_4.md#45-%D0%BA%D0%BE%D0%BC%D0%BF%D0%B8%D0%BB%D1%8F%D1%86%D0%B8%D1%8F-%D0%BC%D0%BE%D0%B4%D1%83%D0%BB%D0%B5%D0%B9-%D0%BF%D0%B5%D1%80%D0%B2%D0%B8%D1%87%D0%BD%D1%8B%D1%85-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%B9)
- [4.6. Исполнение РефалАБ-программ](R_4.md#46-%D0%B8%D1%81%D0%BF%D0%BE%D0%BB%D0%BD%D0%B5%D0%BD%D0%B8%D0%B5-%D1%80%D0%B5%D1%84%D0%B0%D0%BB%D0%B0%D0%B1-%D0%BF%D1%80%D0%BE%D0%B3%D1%80%D0%B0%D0%BC%D0%BC)
- [4.7. Средства отладчика](R_4.md#47-%D1%81%D1%80%D0%B5%D0%B4%D1%81%D1%82%D0%B2%D0%B0-%D0%BE%D1%82%D0%BB%D0%B0%D0%B4%D1%87%D0%B8%D0%BA%D0%B0)
  - [4.7.1. Вызов отладчика](R_4.md#471-%D0%B2%D1%8B%D0%B7%D0%BE%D0%B2-%D0%BE%D1%82%D0%BB%D0%B0%D0%B4%D1%87%D0%B8%D0%BA%D0%B0)
  - [4.7.2. Управление остановом](R_4.md#472-%D1%83%D0%BF%D1%80%D0%B0%D0%B2%D0%BB%D0%B5%D0%BD%D0%B8%D0%B5-%D0%BE%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BE%D0%BC)
  - [4.7.3. Управление прокруткой](R_4.md#473-%D1%83%D0%BF%D1%80%D0%B0%D0%B2%D0%BB%D0%B5%D0%BD%D0%B8%D0%B5-%D0%BF%D1%80%D0%BE%D0%BA%D1%80%D1%83%D1%82%D0%BA%D0%BE%D0%B9)
  - [4.7.4. Перехват останова по неотождествлению](R_4.md#474-%D0%BF%D0%B5%D1%80%D0%B5%D1%85%D0%B2%D0%B0%D1%82-%D0%BE%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%B0-%D0%BF%D0%BE-%D0%BD%D0%B5%D0%BE%D1%82%D0%BE%D0%B6%D0%B4%D0%B5%D1%81%D1%82%D0%B2%D0%BB%D0%B5%D0%BD%D0%B8%D1%8E)

[Приложения](R_5.md#%D0%BF%D1%80%D0%B8%D0%BB%D0%BE%D0%B6%D0%B5%D0%BD%D0%B8%D1%8F)
- [Приложение А. Алфавитный список библиотечных функций](R_5.md#%D0%BF%D1%80%D0%B8%D0%BB%D0%BE%D0%B6%D0%B5%D0%BD%D0%B8%D0%B5-%D0%B0)
- [Приложение Б. Алфавитный список библиотечных пустых функций](R_5.md#%D0%BF%D1%80%D0%B8%D0%BB%D0%BE%D0%B6%D0%B5%D0%BD%D0%B8%D0%B5-%D0%B1)
- [Приложение В. Алфавитный список библиотечных спецификаторов](R_5.md#%D0%BF%D1%80%D0%B8%D0%BB%D0%BE%D0%B6%D0%B5%D0%BD%D0%B8%D0%B5-%D0%B2)
- [Приложение Г. Алфавитный список интерфейсных функций](R_5.md#%D0%BF%D1%80%D0%B8%D0%BB%D0%BE%D0%B6%D0%B5%D0%BD%D0%B8%D0%B5-%D0%B3)
- [Приложение Д. Список использованных источников](R_5.md#%D0%BF%D1%80%D0%B8%D0%BB%D0%BE%D0%B6%D0%B5%D0%BD%D0%B8%D0%B5-%D0%B4)

