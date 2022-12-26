# Требования к проекту

---

[//]: # (TODO: ReWrite to SRS)

## Содержание

[1 Введение](#1-введение)  
[1.1 Глоссарий](#11-Глоссарий)  
[1.2 Назначение](#12-назначение)  
[1.3 Бизнес-требования](#13-бизнес-требования)  
[1.3.1 Исходные данные](#131-исходные-данные)  
[1.3.2 Возможности бизнеса](#132-возможности-бизнеса)  
[1.3.3 Границы проекта](#133-границы-проекта)  
[1.4 Аналоги](#14-аналоги)  
[2 Требования пользователя](#2-требования-пользователя)  
[2.1 Программные интерфейсы](#21-программные-интерфейсы)  
[2.2 Интерфейс пользователя](#22-интерфейс-пользователя)  
[2.3 Характеристики пользователей](#23-характеристики-пользователей)  
[2.3.1 Классы пользователей](#231-классы-пользователей)  
[2.3.2 Аудитория приложения](#232-аудитория-приложения)  
[2.3.2.1 Целевая аудитория](#2321-целевая-аудитория)  
[2.3.2.1 Побочная аудитория](#2322-побочная-аудитория)  
[2.4 Предположения и зависимости](#24-предположения-и-зависимости)  
[3 Системные требования](#3-системные-требования)  
[3.1 Функциональные требования](#31-функциональные-требования)  
[3.1.1 Основные функции](#311-основные-функции)  
[3.1.1.1 Вход пользователя в приложение](#3111-вход-пользователя-в-приложение)  
[3.1.1.2 Наличие уведомлений](#3112-наличие-уведомлений)  
[3.1.1.3 Изменение уведомлений](#3113-изменение-уведомлений)  
[3.1.1.4 Выход зарегистрированного пользователя из учётной записи](#3114-выход-зарегистрированного-пользователя-из-учётной-записи)  
[3.1.1.5 Регистрация нового пользователя после входа в приложение](#3115-регистрация-нового-пользователя-после-входа-в-приложение)  
[3.1.2 Ограничения и исключения](#312-ограничения-и-исключения)  
[3.2 Нефункциональные требования](#32-нефункциональные-требования)  
[3.2.1 Атрибуты качества](#321-атрибуты-качества)  
[3.2.1.1 Требования к удобству использования](#3211-требования-к-удобству-использования)  
[3.2.1.2 Требования к безопасности](#3212-требования-к-безопасности)  
[3.2.2 Внешние интерфейсы](#322-внешние-интерфейсы)  
[3.2.3 Ограничения](#323-ограничения)

# 1 Введение

## 1.1 Глоссарий

Курс валют - цена денежной единицы одной страны, выраженная в денежной 
единице другой.  
Вклад - сумма денег, переданная лицом с целью получения доходов в виде 
процентов, образующихся в ходе финансовых операций с вкладом.  
Архивированные курсы - в большинстве случаев график курсов купли/продажи 
определённого курса валют.  
Уведомления на курс - уведомление, которое будет приходить при достижении 
поставленной суммы купли или продажи определённой валюты в любом или 
конкретном банке.

## 1.2 Назначение

В этом документе будут описаны функциональные и нефункциональные требования к
мультиплатформенному приложению "MoneyWatch". Этот документ предназначен для
команды, которая будет реализовывать и проверять корректность работы приложения.

## 1.3 Бизнес-требования

### 1.3.1 Исходные данные

Множество людей любой возрастной категории зачастую нуждаются в получении
актуального курса валют для различных целей. Однако существующие аналоги либо
сложны для восприятия пользователем, либо страдают от нехватки того или иного
функционала. В связи с этим, с курсом валют зачастую возникают недопонимания, к
примеру, в каком обменнике выгоднее менять деньги, в какую валюту на данный
момент сейчас лучше вкладываться и как поменять деньги по интернету. Из этого
следует, что большинству нужно просто зайти в приложение или на сайт и узнать
именно ту информацию, что им нужна, будь то просто курс валют или же
архивированные курсы. Наши разработчики будут добиваться того, чтобы человек с
любым навыком использования компьютера или телефона смог интуитивно разобраться
в нашем приложении.

### 1.3.2 Возможности бизнеса

Большинство людей хотят иметь возможность мгновенного получения информации об
актуальном курсе валют, графиках колебания курса или же утечках, причём люди эти
могут быть абсолютно любого уровня технической грамотности. Подобное приложение
позволит им тратить намного меньше времени на поиск необходимой валюты, банка и
истории. Интерфейс, спроектированный с учётом этих особенностей, и своевременная
поддержка приложения позволят увеличить приток пользователей данного приложения
многократно. Будет прилагаться возможность ставить уведомления на курс
каких-то валют. При персональном аккаунте максимальное количество
уведомлений может достигать до 3 штук бесплатных и до 10 штук платных. При
бизнес-аккаунте ограничение на уведомления снимаются. Кроме этого, на нашем
сайте будет список всех актуальных криптовалют с их конвертацией в
государственные валюты.

### 1.3.3 Границы проекта

Приложение без обязательной регистрации "MoneyWatch" позволит пользователям
просматривать актуальные курсы валют, рассчитывать выгоднейший обмен, смотреть
графики курсов в прошлом. Также в приложении будет необязательная регистрация,
которая позволит ставить специфичные настройки для каждого пользователя, к
примеру, уведомления, когда курс какой-то из валют достигает некоторой границы.

## 1.4 Аналоги

Обзор аналогов приведён в
документе [overview_of_analogues](./Requirements/overview_of_analogues.md).

# 2 Требования пользователя

## 2.1 Программные интерфейсы

Информация о курсах будет браться с центрального европейского банка валют в
CSV файле.

## 2.2 Интерфейс пользователя

Главный экран сайта.  
![Главное окно](./Requirements/Mockups/main_page.png)  
Окно регистрации нового пользователя.  
![Окно регистрации](./Requirements/Mockups/register.png)  
Окно входа для зарегистрированного пользователя.  
![Окно входа](./Requirements/Mockups/sign_in.png)
Окно конвертера валют
![Окно конвертера1](./Requirements/Mockups/converter1.png)
Окно конвертера после нажатия кнопки переключения курса
![Окно конвертера2](./Requirements/Mockups/converter2.png)
Окно графика курса валют
![График курса](./Requirements/Mockups/charts.png)Окно уведомлений о курсе для
зарегистрированных пользователей
![Окно уведомлений](./Requirements/Mockups/alarms.png)

## 2.3 Характеристики пользователей

### 2.3.1 Классы пользователей

| Класс пользователей             | Описание                                                                                                                        |
|:--------------------------------|:--------------------------------------------------------------------------------------------------------------------------------|
| Анонимные пользователи          | Пользователи, которые не хотят регистрироваться в приложении. Имеют доступ к частичному функционалу.                            |
| Зарегистрированные пользователи | Пользователи, которые вошли в приложение под своим именем. Имеют доступ к полному функционалу. Могут ставить уведомления курсов |

### 2.3.2 Аудитория приложения

#### 2.3.2.1 Целевая аудитория

Люди любой возрастной категории, обладающие минимальными навыками работы с
ПК, интересующиеся актуальными курсами валют и уведомлениями, связанными с ними.

#### 2.3.2.2 Побочная аудитория

Люди средней возрастной категории, бизнесмены, заинтересованные в заработке
на курсах валют.

## 2.4 Предположения и зависимости

1. Приложение не работает при отсутствии подключения к Интернету;
2. Приложение не позволяет добавить новые уведомления, если места закончились.

# 3 Системные требования

## 3.1 Функциональные требования

### 3.1.1 Основные функции

#### 3.1.1.1 Вход пользователя в приложение

**Описание.** Пользователь имеет возможность использовать приложение без
создания собственного аккаунта либо войдя в свою учётную запись.

| Функция                                                               | Требования                                                                                                                                            | 
|:----------------------------------------------------------------------|:------------------------------------------------------------------------------------------------------------------------------------------------------|
| Вход в приложение без создания собственного профиля.                  | Приложение предоставляет возможность войти в приложение анонимно.                                                                                     |
| <a name="registration_requirements"/>Регистрация нового пользователя. | Приложение должно запросить у пользователя ввести личные для создания учётной записи. Пользователь должен либо ввести данные, либо отменить действие. |
| *Пользователь с таким именем существует.*                             | *Приложение должно известить пользователя об ошибке регистрации и запросить ввод. Пользователь должен либо ввести псевдоним, либо отменить действие.* |
| Вход зарегистрированного пользователя в приложение.                   | Приложение направляет пользователя на вкладку личных уведомлений.                                                                                     |

#### 3.1.1.2 Наличие уведомлений

**Описание.** Зарегистрированный пользователь имеет возможность изменять
уведомления о курсе и ставить новые.

| Функция                | Требования                                                                            | 
|:-----------------------|:--------------------------------------------------------------------------------------|
| Добавление уведомлений | Приложение должно предоставить пользователю страницу с добавлением личных уведомлений |
| Изменение уведомлений  | Приложение должно предоставить пользователю страницу с изменением личных уведомлений  |

#### 3.1.1.3 Изменение уведомлений

**Описание.** После захода в сессию пользователь имеет возможность изменять
уведомления о курсе и выставлять новые

| Функция                   | Требования                                                                                       | 
|:--------------------------|:-------------------------------------------------------------------------------------------------|
| Изменение валюты          | Приложение предоставляет возможность изменять валюту, по которой ставится уведомление            |
| Изменение курса           | Приложение предоставляет возможность изменять количество валюты, по которой ставится уведомление |
| Изменить курс на обратный | Приложение предоставляет возможность быстро изменить курс валюты на противоположный.             |

#### 3.1.1.4 Выход зарегистрированного пользователя из учётной записи

**Описание.** Зарегистрированный пользователь имеет возможность выйти из учётной
записи.

**Требование.** Приложение должно предоставить зарегистрированному пользователю
возможность выйти из учётной записи с возвратом к окну входа в приложение.

#### 3.1.1.5 Регистрация нового пользователя после входа в приложение

**Описание.** Анонимный пользователь имеет возможность зарегистрироваться в
приложении.

**Требование.** Приложение должно предоставить анонимному пользователю
возможность [зарегистрироваться в приложении](#registration_requirements).

### 3.1.2 Ограничения и исключения

1. Приложение функционирует в полном наборе возможностей только при наличии
   подключения к Интернету;
2. Приложение может работать некорректно на неподходящем или слишком слабом
   аппаратном обеспечении или неподдерживаемых операционных системах.

## 3.2 Нефункциональные требования

### 3.2.1 Атрибуты качества

#### 3.2.1.1 Требования к удобству использования

1. Доступ к основным функциям приложения не более чем за две операции;
2. Функциональные элементы не перегружают экран;

#### 3.2.1.2 Требования к безопасности

1. Приложение предоставляет возможность просмотра и редактирования
   уведомлений профиля только зарегистрированного пользователя.
2. Для совершения покупок (к примеру дополнительных мест для уведомлений)
   требуется предпринять дополнительные меры безопасности во избежание потери
   денежных средств.

### 3.2.2 Внешние интерфейсы

Окна приложения удобны для использования продолжительное время:

* функциональные элементы не утомляют глаза.
* функциональные элементы линейно распределены по экрану.

### 3.2.3 Ограничения

1. Приложение реализовано на rust и rocket web-версия. Python и PyQt6 -
   Desktop-версия;
2. Курсы валют хранятся в базе данных для последующей оценки и составления
   их графиков.