`passgen` is a command-line utility for generating random passwords. It uses `/dev/urandom` as a source of randomness.

## Installation

```
git clone https://github.com/jealousydx/passgen
cd passgen
make
sudo make install
```

## Usage

```
passgen [OPTIONS]
Generate random passwords.

Options:
  -L <length>    Set password length
  -N <count>     Generate multiple passwords
  -h             Show this help message
```

## Example
Generate 5 passwords of length 16
```
passgen -L 16 -N 5
```
