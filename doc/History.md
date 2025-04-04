История РефалАБ
--------------------

Рефал - язык манипулирования символьными объектами: текстами,
формулами, программами и т.п. Программа на Рефале состоит из
функций, которые могут определяться друг через друга, т.е.
рекурсивно. Отсюда и название: АЛгоритмический язык РЕкурсивных
Функций.

Язык Рефал был создан В. Турчиным [Тур 66] в качестве метаязыка
для описания семантики других языков. Впоследствии, в результате
появления достаточно эффективных реализаций на ЭВМ он стал
находить практическое использование в качестве языка
программирования.

Как известно минимальная версия языка Рефал получила название
Базисный рефал [Тур 74]. Диалект Базисного Рефала под названием
Рефал-2 [Клр 86, Клр87] был реализован на многих типах
отечественных ЭВМ и долгое время играл роль де-факто стандарта
языка Рефал.

В 80-е годы Сергеем Романенко Рефал-2 был реализован на языке
PLI для машин отечественной серии ЕС ЭВМ. Но наступала эра
персональных машин, а машины ЕС ЭВМ сходили со сцены. Два
аспиранта Владимира Хорошевского (Вячеслав Шерстнев и Алексей
Алешин) перекодировали эту PLI реализацию на C для экспериментов
по расширению средствами работы с БД для экcпертных систем. 

Так бы эта работа и ушла в "корзину", если бы не Александр Красовский,
который привел ее в состояние, "изоморфное" PLI-шной реализации,
а документацию в соответствие с новой реализацией на C 
(в частности, интерфейс был переписан с PLI на С), и изготовил в
1991 г. дистрибутив Refal-2, который был рассчитан на совместное
использование с популярными в то время системами
программирования Turbo-C, Quick-C, MSC, VAX-11, PDP-11. 
Однако широкого распространения эта версия не получила, 
скорее всего из-за недостатка рекламы.

Эта реализация языка Рефал-2 в 2005 году переведена 
Леонидом Белоусом на платформы Windows (Windows-95/98/ME/NT/2000/XP) и 
UNIX (FreeBSD, Linux).

В 2024 году мною на основе реализации
[Рефал-2](http://www.refal.net/~belous/index-r.htm) Леонида Белоуса
создан язык программирования РефалАБ (RefalAB),
являющийся диалектом языка Рефал-2.

--Александр Бочаров
https://github.com/Aleksandr3Bocharov


ЛИТЕРАТУРА:

[Тур 66]
В.Ф.Турчин. Метаязык для формального описания алгоритмических
языков. - В сб.: Цифровая вычислительная техника и
программирование, М.:Сов. Радио, 1966, с.116-124.

[Тур 74]
В.Ф.Турчин. Базисный Рефал, описание языка и основные приемы
программирования. Фонд алгоритмов и программ в отрасли
"Строительство". ЦНИПИАСС, Москва, 1971.

[КлР 86]
Ан.В.Климов, С.А.Романенко. Система программирования Рефал-2 для
ЕС ЭВМ. Описание библиотеки функций. М.:ИПМ им.М.В.Келдыша АН
СССР, 1986, препринт N 200. - 38 с.

[КлР 87]
Ан.В.Климов, С.А.Романенко. Система программирования Рефал-2 для
ЕС ЭВМ. Описание входного языка. М.:ИПМ им.М.В.Келдыша АН СССР, 1987. - 52 с.
