# NASA Core Flight Executive (cFE)

## Description
"The Core Flight Executive is a portable, platform independent embedded
system framework developed by NASA Goddard Space Flight Center. This
framework is used as the basis for the flight software for satellite data
systems and instruments, but can be used on other embedded systems."
-- http://sourceforge.net/projects/coreflightexec/

Additional documentation can be found in:
* [cfe-OSS-readme.txt](./cfe-OSS-readme.txt)
* [docs](./docs/)
* [cfe/docs](./cfe/docs/)

## Setting Up Development Environment
1. Clone the `devops` projects into a this project's parent directory:

```bash
   cd ..; git clone https://github.com/yorku-qb50/devops.git
```

2. Then update the base box and start the machine:

```bash
   cd devops
   vagrant box update
   vagrant up
```

   This will create an Eclipse workspace in the parent directory.
3. Connect to the machine via PuTTY and X11 (Xming) on `localhost:2222`
   using the credentials: username: `vagrant` and password: `vagrant`.
4. In the remote terminal, execute the commands:

```bash
   cd workspace/qb50-cfe/.settings
   chmod +x mission-cfe.launch.sh
   ./mission-cfe.launch.sh
```

5. In the remote terminal, execute the command: `eclipse &` and when
   prompted set the workspace to `/home/vagrant/workspace`.

## Sources
* http://opensource.gsfc.nasa.gov/projects/cfe/index.php
* http://sourceforge.net/projects/coreflightexec/ (cFE-6.4.2c-OSS-release.tar.gz)

## Dependecies
* https://github.com/nasa/osal

## License
* [SUA_Open_Source_cFE 6 1_GSC-16232.pdf](SUA_Open_Source_cFE 6 1_GSC-16232.pdf)
