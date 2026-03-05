# 2026_Analysis_jansson

**Autorka:** Marijana Čupovič \
**Broj indeksa:** 1018/2025 \
**Kurs:** Verifikacija softvera 

## Jansson

Projekat je rađen nad bibliotekom jansson koja služi za kodiranje, dekodiranje i manipulaciju JSON datotekama.

**Osnovne informacije:**
- *Repozitorijum:* https://github.com/akheron/jansson
- *Jezik:* C
- *Analizirana grana:* master
- *Heš komita:* 1eb7a81

---

## Korišćeni alati i tehnike

| # | Alat | Kategorija  | Opis |
|---|------|-----------|------|
| 1 | clang-format | Formatiranje | Stilska provera |
| 2 | memcheck | Profajliranje | Rukovanje memorijom |
| 3 | lizard | Kompleksnost | Ciklomatska složenost |
| 4 | flawfind | Bezbednost | Sigurnosne ranjivosti |
| 5 | CUnit | Testiranje | Testiranje jedinica koda |
| 6 | lcov  | Pokrivenost| Praćenje pokrivenosti testovma|
| 7 | scan-build | Statička analiza | Simboličko izvršavanje  |

## Zaključak

Nakon analize *Jansson* biblioteke se može uočiti da je, iako jako kompleksna, dobro napisana. Pazilo se na moguće greške, performanse i preciznost, kao i na testiranje kreiranog koda. Kod koji je analiziran je jako složen, ali su programerske prakse kreatora uredne i prate bezbednosna pravila. Nema curenja memorije, a rad sa rizičnim funkcijama je pedantno odrađen.