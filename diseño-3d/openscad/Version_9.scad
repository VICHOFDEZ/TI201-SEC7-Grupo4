// ==========================================================
// DETECTOR DE ESTACIONAMIENTO - V13
// Tránsito en X; eje mayor en Y (perpendicular al tránsito)
// Atornillado desde arriba. PLA. Medidas en mm.
// Orejas de unión integradas al contorno parabólico
// ==========================================================

// ---------- QUÉ MOSTRAR / EXPORTAR ----------
// "explosionado" | "ensamblado" | "base" | "cubierta" | "ventana" | "oring"
pieza      = "ensamblado";
separacion = 80;
corte      = false;
mostrar_electronica = true;

$fn = 96;
eps = 0.01;
N_seg = 40;     // segmentos de la curva de la cúpula

// ---------- BASE ----------
h_base = 8;
base_a = 94;    // semieje Y (perpendicular al tránsito)
base_b = 82;    // semieje X (sentido del tránsito)

// ---------- TORNILLOS AL SUELO (desde arriba, embutidos) ----------
d_tornillo = 3.4;
anclajes_suelo = [[0, 86], [0, -86], [74, 0], [-74, 0]];

// ---------- UNIONES CUBIERTA-BASE (orejas integradas) ----------
d_insert    = 4.2;   // inserto M3 térmico, ajustar a la ficha
prof_insert = 5;
union_pos   = [[50, 64], [-50, 64], [-50, -64], [50, -64]];
re_bot      = 6.5;   // radio de la oreja en la base (z = h_base)
re_top      = 5;     // radio de la oreja en su tope (alrededor del tornillo)
alto_oreja  = 8;     // la oreja termina en z = h_base + alto_oreja (16)

// ---------- CUBIERTA (parábola) ----------
alto_cubierta = 55;
H_top         = h_base + alto_cubierta;   // 63
espesor       = 3.5;                      // pared lateral
espesor_techo = 6;                        // techo de la cúpula
techo_z       = H_top - espesor_techo;    // 57

a_bot = 80;  b_bot = 68;   // semiejes en la base de la cubierta
a_top = 14;  b_top = 14;   // plataforma plana de la ventana

// ---------- VENTANA (plástico de DVD) ----------
grosor_ventana = 1.5;
r_ventana      = 9;
r_plancha      = 10.5;

// ---------- O-RING (142 x 2,5) ----------
oring_d     = 2.5;
prof_ranura = 2.0;
og_a = 78.5;   // semieje Y de la línea central de la ranura
og_b = 66.5;   // semieje X de la línea central de la ranura

// ---------- ELECTRÓNICA ----------
bat_w = 30;  bat_l = 112;  bat_h = 26;  bat_c = [0, 0];
esp_w = 25;  esp_l = 50;   esp_c = [35, 0];  esp_pcb = 1.6;
esp_z = h_base + 3;
sen_l = 15;  sen_w = 10;   sen_h = 13;  sen_c = [0, 0];
sen_z0 = techo_z - sen_h - 0.5;     // 0,5 mm de holgura bajo el techo
bandeja_h = 2;
bandeja_z = sen_z0 - bandeja_h;
pilar_d = 3;

post_x = [esp_c[0] - esp_w/2 + 3, esp_c[0] + esp_w/2 - 3];
post_y = [esp_c[1] - esp_l/2 + 3, esp_c[1] + esp_l/2 - 3];

// ==========================================================
// FUNCIONES
// ==========================================================
// Semiejes de la cúpula a la altura z (parábola)
function parab(z, v_bot, v_top, ofs) =
    v_top + (v_bot - v_top) * (1 - pow((z - h_base) / (H_top - h_base), 2)) - ofs;
function A_(z) = parab(z, a_bot, a_top, 0);   // semieje Y exterior
function B_(z) = parab(z, b_bot, b_top, 0);   // semieje X exterior

// Radio de la oreja a la altura z: se afina hacia arriba y desaparece sobre z = 16
function re_oreja(z) =
    (z <= h_base + alto_oreja)
        ? re_bot + (re_top - re_bot) * (z - h_base) / alto_oreja
        : 0;

// ==========================================================
// MÓDULOS AUXILIARES
// ==========================================================
module eliptico(z0, z1, a0, b0, a1_, b1_) {
    translate([0, 0, z0])
        linear_extrude(height = z1 - z0, scale = [b1_ / b0, a1_ / a0])
            scale([b0, a0]) circle(r = 1);
}

// Cavidad interior (solo elipse, sin orejas)
module cuerpo_parabolico(z0, z1, ofs) {
    for (i = [0 : N_seg - 1]) {
        za = z0 + (z1 - z0) * i / N_seg;
        zb = z0 + (z1 - z0) * (i + 1) / N_seg;
        eliptico(za, zb,
                 parab(za, a_bot, a_top, ofs), parab(za, b_bot, b_top, ofs),
                 parab(zb, a_bot, a_top, ofs), parab(zb, b_bot, b_top, ofs));
    }
}

// Contorno de una altura: óvalo + orejas unidas con tangencia (hull)
module perfil2d(z) {
    r = re_oreja(z);
    scale([B_(z), A_(z)]) circle(r = 1);
    if (r > 0)
        for (p = union_pos)
            hull() {
                scale([B_(z), A_(z)]) circle(r = 1);
                translate(p) circle(r = r);
            }
}

// Cuerpo exterior con orejas: cada tramo es el casco convexo entre dos contornos
module cuerpo_con_orejas() {
    for (i = [0 : N_seg - 1]) {
        za = h_base + alto_cubierta * i / N_seg;
        zb = h_base + alto_cubierta * (i + 1) / N_seg;
        hull() {
            translate([0, 0, za])       linear_extrude(height = eps) perfil2d(za);
            translate([0, 0, zb - eps]) linear_extrude(height = eps) perfil2d(zb);
        }
    }
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
    translate([0, 0, h_base - prof_ranura])
        linear_extrude(height = prof_ranura + eps)
            difference() {
                scale([68.25, 80.25]) circle(r = 1);
                scale([64.75, 76.75]) circle(r = 1);
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
        for (p = anclajes_suelo) taladro(p, -1, h_base);
        for (p = union_pos)
            translate([p[0], p[1], h_base - prof_insert])
                cylinder(h = prof_insert + 1, d = d_insert);
    }
}

// ==========================================================
// CUBIERTA
// ==========================================================
module cavidad() {
    cuerpo_parabolico(h_base - 1, techo_z, espesor);
}

module soporte_sensor() {
    translate([-10, -7, bandeja_z]) cube([20, 14, bandeja_h]);
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
                cuerpo_con_orejas();
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
    color("black")
    translate([0, 0, h_base - prof_ranura])
        linear_extrude(height = oring_d)
            difference() {
                scale([og_b + 1.25, og_a + 1.25]) circle(r = 1);
                scale([og_b - 1.25, og_a - 1.25]) circle(r = 1);
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
    else if (pieza == "cubierta") translate([0, 0, -h_base]) cubierta();
    else if (pieza == "ventana")  cylinder(h = grosor_ventana, r = r_plancha);
    else if (pieza == "oring")    translate([0, 0, -(h_base - prof_ranura)]) oring_mod();
}