from dataclasses import dataclass

import requests
from bs4 import BeautifulSoup


@dataclass
class Currency:
    buy: float
    sell: float

    def __init__(self, currency: tuple):
        self.buy = currency[0]
        self.sell = currency[1]


@dataclass
class BankInfo:
    name: str
    USD: Currency
    EUR: Currency
    RUB100: Currency
    EUR_USD: Currency


DUPLICATED_BANKS = ["«Заначка»", "Онлайн-обменник Nembo", "Up «Суперкурс»", "InSync by Alfa-Bank", "Paritetbank"]


def grub_exchange_rate() -> dict:
    source = requests.get('https://myfin.by/bank/kursy_valjut_nbrb').text
    soup = BeautifulSoup(source, 'lxml')
    exchange_rate_table = soup.find('table', class_='default-table').find('tbody').find_all('tr')
    rate_from_BY = dict()
    rate_from_BY['BYN'] = 1

    for i in range(3):
        line = exchange_rate_table[i]

        # Can be line.next.next_sibling.text
        rate_from_BY[line.next.next_sibling.next_sibling.next_sibling.text] \
            = round(float(line.next.next_sibling.text) / float(
            line.next.next_sibling.next_sibling.next_sibling.next_sibling.next), 4)
        # can be line.next.next_sibling.next_sibling.next_sibling.next
    return rate_from_BY


def grub_currencies_rate() -> list:
    """Return tuple of lists, which contain next strings: bank names, USD rate, EUR rate, RUB100 rate, EUR_USD rate"""
    source = requests.get('https://myfin.by/currency/minsk').text
    soup = BeautifulSoup(source, 'lxml')
    table = soup.find('tbody', class_='sort_body')

    banks = table.find_all('tr')
    banks_info = dict()
    USD_list = list()
    EUR_list = list()
    RUB100_list = list()
    EUR_USD_list = list()

    for bank in banks:
        if len(banks_info.keys()) >= 20:
            break
        try:
            bank_rate = list()
            name = ''

            # Collect all information about bank
            for bank_info in bank:
                # ! DO NOT Rewrite to regEx (Extremely slow!!)
                # If bank doesn't sell currencies
                if str(bank_info) == '<td class="currencies-courses__currency-cell ' \
                                     'currencies-courses__currency-cell--empty">-</td>':
                    bank_rate.append(None)

                # Bank name
                elif bank_info.find('img'):
                    # if bank_info.span.img is not None:
                    name = str(bank_info.span.img).split('\"')[1]
                    if name in DUPLICATED_BANKS:
                        break

                # Bank currency
                else:
                    bank_rate.append(float(bank_info.span.text))

            if name not in DUPLICATED_BANKS:
                banks_info[name] = bank_rate

        except Exception as e:
            # Exceptions with NoneType objects (collect only bank currencies)
            continue

    bank_names = list()
    for bank_name in banks_info.keys():
        bank_names.append(bank_name)

    # Parse data
    currencies = [USD_list, EUR_list, RUB100_list, EUR_USD_list]
    number_dict = {'USD': 0, 'EUR': 2, 'RUB_100': 4, 'EUR_USD': 6}
    for x, currency in enumerate(number_dict.values()):
        for bank in banks_info:
            currencies[x].append((banks_info[bank][currency], banks_info[bank][currency + 1]))

    banks_info = list()
    for (name, USD, EUR, RUB100, EUR_USD) in zip(bank_names, USD_list, EUR_list, RUB100_list, EUR_USD_list):
        banks_info.append(BankInfo(name, Currency(USD), Currency(EUR), Currency(RUB100), Currency(EUR_USD)))

    return banks_info
