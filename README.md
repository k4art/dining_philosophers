# Dining Philosophers

## Output
By default, philosophers report their actions by printing their associated letters on a colored background:
- dining - green,
- thinking - white,
- waiting forks availability - red.

## Build

Use `make debug` or `make release` to build.

It is possible to report only dining events, for example:

```bash
make release LOG_ONLY_DINING=1
```
