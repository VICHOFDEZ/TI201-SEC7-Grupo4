// ==========================================================
// DETECTOR DE ESTACIONAMIENTO - V9 (ovalado)
// Tránsito en el eje X; eje mayor perpendicular (eje Y)
// Atornillado desde arriba: 4 uniones (orejas) + 4 anclajes al suelo
// PLA. Medidas en mm.
// ==========================================================

// ---------- QUÉ MOSTRAR / EXPORTAR ----------
// "explosionado" | "ensamblado" | "base" | "cubierta" | "ventana" | "oring"
pieza      = "ensamblado";
separacion = 80;
corte      = false;
mostrar_electronica = true;

$fn = 96;
eps = 0.01;

// ---------- BASE ----------
h_base  = 8;
base_a  = 86;       // semieje Y (perpendicular al tránsito)
base_b  = 74;       // semieje X (sentido del tránsito)

// ---------- TORNILLOS (desde arriba, embutidos) ----------
d_tornillo = 3.4;   // paso M3
anclajes_suelo = [[0, 81], [0, -81], [69, 0], [-69, 0]];

// ---------- UNIONES CUBIERTA-BASE (orejas) ----------
d_insert    = 4.2;  // inserto M3 térmico, ajustar a la ficha del inserto
prof_insert = 5;
alto_oreja  = 6;
union_pos = [ [49.5, 56.6], [-49.5, 56.6], [-49.5, -56.6], [49.5, -56.6] ];

// ---------- CUBIERTA (perfil ovalado) ----------
alto_cubierta = 55;
H_top   = h_base + alto_cubierta;   // 63
espesor = 3;
techo_z = H_top - espesor;          // 60

// Escalones: semiejes [Y, X] por altura
a1 = 76; b1 = 64;  za1 = 34; zl1 = 37;   // escalón 1 y rampa 1
a2 = 60; b2 = 50;  z2  = 49; zl2 = 51;   // escalón 2 y rampa 2
a3 = 46; b3 = 38;                        // inicio de la tapa cónica
a4 = 14; b4 = 14;                        // plataforma plana (ventana)

// ---------- VENTANA (plástico de DVD) ----------
grosor_ventana = 1.5;
r_ventana      = 9;     // apertura bajo el sensor
r_plancha      = 10.5;  // alojamiento de la plancha

// ---------- O-RING (cordón 135 x 2,5, aprox. ovalado) ----------
oring_d     = 2.5;
prof_ranura = 2.0;

// ---------- ELECTRÓNICA ----------
bat_w = 30;  bat_l = 112;  bat_h = 26;  bat_c = [0, 0];   // batería a lo largo de Y
esp_w = 25;  esp_l = 50;   esp_c = [35, 0];  esp_pcb = 1.6;
esp_z = h_base + 3;
sen_l = 15;  sen_w = 10;   sen_h = 13;  sen_c = [0, 0];
sen_z0 = techo_z - sen_h;            // 47
bandeja_h = 2;
bandeja_z = sen_z0 - bandeja_h;
pilar_d = 3;

post_x = [esp_c[0] - esp_w/2 + 3, esp_c[0] + esp_w/2 - 3];
post_y = [esp_c[1] - esp_l/2 + 3, esp_c[1] + esp_l/2 - 3];

// ==========================================================
// MÓDULOS AUXILIARES
// ==========================================================
// Tronco elíptico: pasa de semiejes (a0 Y, b0 X) a (a1 Y, b1 X)
module eliptico(z0, z1, a0, b0, a1_, b1_) {
    translate([0, 0, z0])
        linear_extrude(height = z1 - z0, scale = [b1_ / b0, a1_ / a0])
            scale([b0, a0]) circle(r = 1);
}

// Taladro con avellanado en la cara superior (z1)
module taladro(p, z0, z1) {
    translate([p[0], p[1], z0]) cylinder(h = z1 - z0 + eps, d = d_tornillo);
    translate([p[0], p[1], z1 - 1.6]) cylinder(h = 1.6 + eps, d1 = d_tornillo, d2 = 6.4);
}

// ==========================================================
// BASE
// ==========================================================
module ranura_oring() {
    // ranura en la cara superior, bajo la pared de la cubierta
    translate([0, 0, h_base - prof_ranura])
        linear_extrude(height = prof_ranura + eps)
            difference() {
                scale([64.25, 76.25]) circle(r = 1);
                scale([60.75, 72.75]) circle(r = 1);
            }
}

module base() {
    difference() {
        union() {
            linear_extrude(height = h_base) scale([base_b, base_a]) circle(r = 1);
            for (x = post_x, y = post_y)
                translate([x, y, h_base - eps]) cylinder(h = 3, d = 4);
        }
        ranura_oring();
        // anclajes al suelo, atornillados desde arriba
        for (p = anclajes_suelo) taladro(p, -1, h_base);
        // pozos para insertos M3 bajo las orejas
        for (p = union_pos)
            translate([p[0], p[1], h_base - prof_insert])
                cylinder(h = prof_insert + 1, d = d_insert);
    }
}

// ==========================================================
// CUBIERTA
// ==========================================================
module envolvente() {
    eliptico(h_base, za1, a1, b1, a1, b1);   // escalón 1
    eliptico(za1, zl1, a1, b1, a2, b2);      // rampa 1
    eliptico(zl1, z2, a2, b2, a2, b2);       // escalón 2
    eliptico(z2, zl2, a2, b2, a3, b3);       // rampa 2
    eliptico(zl2, H_top, a3, b3, a4, b4);    // tapa cónica con plataforma
}

module oreja(p) {
    hull() {
        translate([p[0], p[1], h_base - eps]) cylinder(h = alto_oreja + eps, d = 12);
        translate([0.8 * p[0], 0.8 * p[1], h_base - eps]) cylinder(h = alto_oreja + eps, d = 12);
    }
}

module cavidad() {
    eliptico(h_base - 1, za1, a1 - 3, b1 - 3, a1 - 3, b1 - 3);
    eliptico(za1, zl1, a1 - 3, b1 - 3, a2 - 3, b2 - 3);
    eliptico(zl1, z2, a2 - 3, b2 - 3, a2 - 3, b2 - 3);
    eliptico(z2, zl2, a2 - 3, b2 - 3, a3 - 3, b3 - 3);
    eliptico(zl2, techo_z, a3 - 3, b3 - 3, a4 - 3, b4 - 3);
}

module soporte_sensor() {
    // bandeja horizontal del sensor
    translate([-10, -7, bandeja_z]) cube([20, 14, bandeja_h]);
    // pilares que lo sostienen desde el techo
    for (x = [-10, 10], y = [-6, 6])
        translate([x, y, sen_z0]) cylinder(h = techo_z - sen_z0 + 0.5, d = pilar_d);
}

module ventana_corte() {
    translate([0, 0, techo_z - 1]) cylinder(h = 10, r = r_ventana);
    translate([0, 0, H_top - grosor_ventana]) cylinder(h = 10, r = r_plancha);
}

module cubierta() {
    difference() {
        union() {
            difference() {
                union() {
                    envolvente();
                    for (p = union_pos) oreja(p);
                }
                cavidad();
            }
            soporte_sensor();
        }
        ventana_corte();
        for (p = union_pos) taladro(p, h_base - 1, h_base + alto_oreja);
    }
}

// ==========================================================
// PIEZAS DE MAQUETA (no se imprimen)
// ==========================================================
module oring_mod() {
    // aproximación en sección plana; el real es un cordón redondo
    color("black")
    translate([0, 0, h_base - prof_ranura])
        linear_extrude(height = oring_d)
            difference() {
                scale([62.5 + 1.25, 74.5 + 1.25]) circle(r = 1);
                scale([62.5 - 1.25, 74.5 - 1.25]) circle(r = 1);
            }
}

module ventana_demo() {
    color("cyan", 0.4)
    translate([0, 0, H_top - grosor_ventana])
        cylinder(h = grosor_ventana, r = r_plancha);
}

module bateria() {
    color("dimgray")
    translate([bat_c[0] - bat_w/2, bat_c[1] - bat_l/2, h_base])
        cube([bat_w, bat_l, bat_h]);
}

module esp() {
    color("royalblue")
    translate([esp_c[0] - esp_w/2, esp_c[1] - esp_l/2, esp_z])
        cube([esp_w, esp_l, esp_pcb]);
}

module sensor() {
    color("mediumpurple")
    translate([sen_c[0] - sen_l/2, sen_c[1] - sen_w/2, sen_z0])
        cube([sen_l, sen_w, sen_h]);
}

module seccion() {
    if (corte) difference() { children(); translate([0, -200, -50]) cube([200, 400, 500]); }
    else children();
}

module gris() color("#8d9298") children();

// ==========================================================
// SALIDA
// ==========================================================
seccion() {
    if (pieza == "explosionado") {
        gris() base();
        if (mostrar_electronica) { bateria(); esp(); }
        translate([0, 0, separacion * 0.35]) oring_mod();
        translate([0, 0, separacion]) {
            gris() cubierta();
            ventana_demo();
            if (mostrar_electronica) sensor();
        }
    }
    else if (pieza == "ensamblado") {
        gris() base();
        gris() cubierta();
        oring_mod();
        ventana_demo();
        if (mostrar_electronica) { bateria(); esp(); sensor(); }
    }
    else if (pieza == "base")     base();
    else if (pieza == "cubierta") translate([0, 0, -h_base]) cubierta();   // imprimir con las orejas sobre la cama
    else if (pieza == "ventana")  cylinder(h = grosor_ventana, r = r_plancha);
    else if (pieza == "oring")    translate([0, 0, -(h_base - prof_ranura)]) oring_mod();
}