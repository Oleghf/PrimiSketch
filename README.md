# PrimiSketch

Клонирование репозитория обязательно с сабмодулями:

```bash
git clone --recurse-submodules ***
```

Для работы в VSCode дополнительно требуется явно указать генератор Ninja. В настройки дописать:

```json
"cmake.generator": "Ninja",
"cmake.makeProgram": "${workspaceFolder}/Tools/ninja",
```
