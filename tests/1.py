import requests
import json

# r = requests.get('http://127.0.0.1/api/get/all/journal_table(journal_table)[*;teacher_id[name];methodist_id[]]')
r = requests.get('http://kusjournal.ru/api/get/all/journal_table[*;teacher_id[name];methodist_id[]]')
#r = requests.get('http://127.0.0.1/api/get/all/journal_table')
print(r)
print(r.text)
print(r.json())
print(r.raw)
data = json.loads(r.text)
print(data)
print(len(data['journal_tables']) == 5)
print(len(data['journal_tables']) == 5)
print(data['journal_tables'][0])
#  ['teacher']['name']
#  == 'Ника'
