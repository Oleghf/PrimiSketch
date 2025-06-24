# PrimiSketch

Клонирование репозитория обязательно с сабмодулями:

```bash
git clone --recurse-submodules https://gitlab-klmn-test.ascon.ru/student_internship/khlystun_o.git
```

Для работы в VSCode дополнительно требуется явно указать генератор Ninja. В настройки дописать:

```json
"cmake.generator": "Ninja",
"cmake.makeProgram": "${workspaceFolder}/Tools/ninja",
```
