# xwebrtc

C++ backend for WebRTC in the Jupyter notebook/lab

**xwebrtc is an early developer preview, and is not suitable for general usage yet. Features and implementation are subject to change.**

## Installation

We provide a package for the conda package manager.

- Installing `xwebrtc` and the C++ kernel

```bash
conda install xeus-cling xwebrtc -c QuantStack -c conda-forge
```

Then, the front-end extension must be installed for either the classic notebook or JupyterLab.

- Installing the extensions for the classic notebook

```
conda install widgetsnbextension -c conda-forge
conda install ipywebrtc -c conda-forge
```

## Installation from sources

Or you can directly install it from the sources if you have all the dependencies already installed:

```bash
cmake -D CMAKE_INSTALL_PREFIX=your_install_prefix
make install
```

## Dependencies

All the dependencies of xleaflet are available for the conda package manager.

| `xwebrtc`  | `xwidgets`  |  `xeus`         |
|------------|-------------|-----------------|
|  master    |   ~0.13.0   |  ~0.13          |
|  0.1.0     |   ~0.13.0   |  ~0.13          |

## License

We use a shared copyright model that enables all contributors to maintain the
copyright on their contributions.

This software is licensed under the BSD-3-Clause license. See the [LICENSE](LICENSE) file for details.
