# Driverless-Project-4
Per risolvere questo problema, innanzitutto bisogna vedere cosa si ha come dati, abbiamo:
$$x_{pos} = 500mm y_{pos} = 160mm z_{pos} = 1140mm$$
$$roll = 100°, pitch = 0°, yaw = 90°$$
$$c_x = 636 px, cy = 548 px$$
$$f_x = 241px, f_y = 238px$$
$$u = 795px, v = 467px, d = 2,7m$$
Prima di iniziare a calcolare bisogna avere idea di qual è l'obiettivo: <br>

| World Coords | Camera Coords | Film Coords | Pixel Coords |
| -------- | -------- | -------- | -------- |
| U | X | x | u |
| V | Y | y | v |
| W | Z |  |  |

Lo scopo è di trasformare da "Pixel Coords" a "Camera Coords", per fare questo si inizia usando le "Perspective Projection Equation":
$$x_{cam} = X/Z, y_{cam} = Y/Z$$
$$u = f_x * x_{cam} + c_x$$
$$v = f_y * y_{cam} + c_x$$
Dobbiamo semplicemente riscrivere le equazioni e trasformarle in:
$$x_{cam} = (u - c_x) / f_x$$
$$y_{cam} = (v - c_y) / f_y$$
$$X = x_{cam} * Z$$
$$Y = y_{cam} * Z$$
(sappiamo che Z = d, quindi Z = 2,7m)
Dati gli angoli di Eulero, dobbiamo convertire queste coordinate nelle coordinate del punto, quindi facciamo la trasformazione delle matrici
$$M = M_x(roll) * M_y(pitch) * M_z(yaw)$$
$M_x:$
| 1             | 0            | 0             |    
| ------------- | ------------ | ------------- |
| 0             | cos(roll)    | -sin(roll)    |
| 0             | sin(roll)    | cos(roll)     |

$M_y:$
| cos(pitch)  | 0 | sin(pitch) |
| ----------  | - | ---------- |
| 0           | 1 | 0          |
| -sin(pitch) | 0 | cos(pitch) |

$M_z:$
| cos(yaw)  | -sin(yaw) | 0 |
| --------- | --------- | - |
| sin(yaw)  | cos(yaw)  | 0 |
| 0         | 0         | 1 |

Quindi effettuando la moltiplicazione tra le 3 matrici otteniamo:
$$x_v = (0 * x) + (-1 * y) + (0 * z) + x_{pos}$$
$$y_v = (1 * x) + (0 * y) + (0 * z) + y_{pos}$$
$$y_v = (0 * x) + (0 * y) + (1 * z) + z_{pos}$$

$$x_v = 1,418m$$
$$y_v = 1,941m$$
$$z_v = 3,84m$$
