### Note
- **alpha**: Basically a lower limit of possible scores that a maximixing player can have. We improve this parameter in maximixing player only. Then we compare it with **beta** the value which is not updated in the maximixing stage but in the previous (ancestor) minimizing stages. If the lower limit aka **alpha** goes above or equal to the known **beta** value then there is no use of exploring further the current maximizing stage, as the any value that maximixing stage is going to possibly choose is going to be ignored by the ancestral minimizing stage.

- **beta**: Same as **alpha** - an upper limit of possible scores that a minimizing player can have
