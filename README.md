# Parking Lot Manager (C++)

An object-oriented C++ system for managing parking lots. It records vehicle entries and exits by licence plate, calculates the amount to pay according to parking time, supports monthly subscriptions, and can manage several parking lots across different cities.

The design is built from small, reusable classes: dates, times and licence plates are classes of their own, and they are composed into entry/exit records, parking lots and a multi-lot manager.

> Project developed for the course **Object-Oriented Programming**, BSc in **Electrical and Computer Engineering**, **Instituto Politécnico do Cávado e Ave (IPCA)**, **2nd year**.

---

## Features

- Register vehicle **entry and exit** by licence plate, with date and time
- Calculate the **amount to pay** based on parking time, handling stays within the same day and stays spanning several days
- Track occupancy, free spaces, payments received and the amount still owed by parked vehicles
- **Monthly subscriptions** (`Avenca`) with the subscriber's name, NIF (tax ID), signing date and months paid
- **Multiple parking lots**: list the lots of a city, find the lot where a vehicle is parked, and view a vehicle's history
- History and report printing for a lot or for a single vehicle
- **Input validation:** invalid dates and times are rejected with an exception
- Small text-mode menu to try out the operations

---

## Class overview

| Class | Responsibility |
|---|---|
| `Viatura` | A vehicle, identified by its licence plate |
| `Data` | A calendar date (`DD/MM/YYYY`), with leap-year handling and validation |
| `Hora` | A time of day (`HH:MM:SS`, 24-hour clock), with validation |
| `DataHora` | A date and time combined, inheriting from both `Data` and `Hora` |
| `RegistoES` | An entry/exit record of a vehicle: times, parked and paid status, amount paid and NIF |
| `Avenca` | A monthly subscription, with the subscriber's data and records |
| `Parque` | A single parking lot: capacity, entries and exits, pricing and payments |
| `GestParq` | Manager for a collection of parking lots |

### `Viatura`

Stores the licence plate. Provides getter/setter, `operator==` and `toString()`.

### `Data`

- The default constructor creates an "empty" invalid date (`0/0/0`).
- `Data(int ano, int mes, int dia)` **validates** the date and throws `invalid_argument` if it is invalid.
- Operators: `-` (difference between dates), `>`, `>=`, `==`, `!=`.
- Helpers: `dBissexto()` (leap year), `dValida()`, `toString()`.

### `Hora`

- The default constructor creates an "empty" invalid time (`h = -1`).
- `Hora(int h, int m = 0, int s = 0)` **validates** the time and throws `invalid_argument` if it is invalid.
- Operators: `-`, `+`, `>`, `>=`, `==`, `!=`.
- Helpers: `verificaHora()`, `toString()`.

### `DataHora`

Combines `Data` and `Hora` so a date-time can be created in one line: `DataHora(ano, mes, dia, horas, minutos = 0, segundos = 0)`.

- Operators: `==`, `>=`, `!=`, and `-`, which returns the difference **in minutes**.
- Helpers: `difDeDias()` (difference in days), `minutosAteFimDoDia()` (minutes until midnight), `minutosDesdeInicioDoDia()` (minutes since midnight), `getDataHora()`.

The two minute helpers are what make it easy to split a multi-day stay into partial first day, full days and partial last day.

### `RegistoES`

Holds one vehicle's entry (and, later, exit) as `DataHora` values, plus whether it is still parked, whether it has been paid, the amount paid and the NIF.

- `registaSaida()` records the exit and returns the parking time in minutes.
- `diasEstacionamento()` and `minutosEstacionamento()` compute the stay duration, either with a recorded exit or against a "current" date-time.
- `verificaEstacionament()` / `verificaPagamento()` check parked and paid status.

### `Avenca`

A monthly subscription holding the subscriber's name, NIF, signing date-time and number of months signed (default: 1), plus the entry/exit records made under it.

- `adicionarRegisto()` attaches a record to the subscription.
- `estaPago()` checks whether a given month is covered.
- Two subscriptions are equal when their NIFs are equal.

### `Parque`

`Parque(string cidade, int lotacao = 100, string idparque = "")` creates a lot with a default capacity of 100 spaces.

| Area | Methods |
|---|---|
| Occupancy | `ocupacao()`, `lugaresLivres()`, `estaEstacionado()` |
| Entry/exit | `estaciona()`, `saida()` (returns the amount to pay) |
| Pricing | `valorAPagar()`, `calcularPrecoMesmoDia()`, `calcularPrecoDiaCompleto()` |
| Payments | `recebePagamento()`, `valorTotalPago()`, `valorFaltaPagar()`, `valorTotalParque()` |
| Subscriptions | `setAvenca()`, `temAvencaPaga()`, `listarAvencas()`, `infoClientePorNIF()` |
| Reports | `historicoParque()`, `historicoViatura()`, `ultimoRegisto()`, `tempoTotalDeEstacionamento()` |

**Pricing:** [add the tariff here, e.g. price per minute/hour, daily maximum]

### `GestParq`

Manages a collection of `Parque` objects:

- `registarEntrada()` / `registarSaida()` register a vehicle's entry or exit in a given lot
- `parquesDaCidade()` lists the lots of a city
- `historicoViatura()` prints a vehicle's history
- `cidadeEstacionamento()` shows the city where a vehicle is currently parked

---

## Concepts demonstrated

- Encapsulation, with getters/setters and private members
- Operator overloading (`-`, `+`, `>`, `>=`, `==`, `!=`)
- Multiple inheritance (`DataHora` from `Data` and `Hora`)
- Composition (`RegistoES` contains `Viatura` and `DataHora`; `Parque` manages `RegistoES`; `GestParq` manages `Parque`)
- Constructors with default arguments
- Input validation with exceptions (`invalid_argument`)
- Method overloading (`minutosEstacionamento`)

---

## Building and running

Requires a C++ compiler (for example, `g++`). Compile all the source files together and run the result:

```bash
g++ *.cpp -o parking-lot-manager
./parking-lot-manager
```

---

## Current status

`Parque` and `GestParq` are **not fully functional yet**: some issues with them remain unresolved. The remaining classes (`Viatura`, `Data`, `Hora`, `DataHora`, `RegistoES` and `Avenca`) are complete.

---

## Author

**Ivo Azevedo**
