/*
 * Coldfire generic GPIO support
 *
 * (C) Copyright 2009, Steven King <sfking@fdwdc.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
*/

#include <linux/kernel.h>
#include <linux/init.h>

#include <asm/coldfire.h>
#include <asm/mcfsim.h>
#include <asm/mcfgpio.h>

static struct mcf_gpio_chip mcf_gpio_chips[] = {
  {
    .gpio_chip      = {
      .label      = "NQ",
      .request    = mcf_gpio_request,
      .free     = mcf_gpio_free,
      .direction_input  = mcf_gpio_direction_input,
      .direction_output = mcf_gpio_direction_output,
      .get      = mcf_gpio_get_value,
      .set      = mcf_gpio_set_value,
      .base     = 1,
      .ngpio      = 7,
    },
    .pddr       = (void __iomem *) MCFEPORT_EPDDR,
    .podr       = (void __iomem *) MCFEPORT_EPDR,
    .ppdr       = (void __iomem *) MCFEPORT_EPPDR,
  },
  {
    .gpio_chip      = {
      .label      = "TA",
      .request    = mcf_gpio_request,
      .free     = mcf_gpio_free,
      .direction_input  = mcf_gpio_direction_input,
      .direction_output = mcf_gpio_direction_output,
      .get      = mcf_gpio_get_value,
      .set      = mcf_gpio_set_value_fast,
      .base     = 8,
      .ngpio      = 4,
    },
    .pddr       = (void __iomem *) MCFGPTA_GPTDDR,
    .podr       = (void __iomem *) MCFGPTA_GPTPORT,
    .ppdr       = (void __iomem *) MCFGPTB_GPTPORT,
  },
  {
    .gpio_chip      = {
      .label      = "TB",
      .request    = mcf_gpio_request,
      .free     = mcf_gpio_free,
      .direction_input  = mcf_gpio_direction_input,
      .direction_output = mcf_gpio_direction_output,
      .get      = mcf_gpio_get_value,
      .set      = mcf_gpio_set_value_fast,
      .base     = 16,
      .ngpio      = 4,
    },
    .pddr       = (void __iomem *) MCFGPTB_GPTDDR,
    .podr       = (void __iomem *) MCFGPTB_GPTPORT,
    .ppdr       = (void __iomem *) MCFGPTB_GPTPORT,
  },
  {
    .gpio_chip      = {
      .label      = "QA",
      .request    = mcf_gpio_request,
      .free     = mcf_gpio_free,
      .direction_input  = mcf_gpio_direction_input,
      .direction_output = mcf_gpio_direction_output,
      .get      = mcf_gpio_get_value,
      .set      = mcf_gpio_set_value_fast,
      .base     = 24,
      .ngpio      = 4,
    },
    .pddr       = (void __iomem *) MCFQADC_DDRQA,
    .podr       = (void __iomem *) MCFQADC_PORTQA,
    .ppdr       = (void __iomem *) MCFQADC_PORTQA,
  },
  {
    .gpio_chip      = {
      .label      = "QB",
      .request    = mcf_gpio_request,
      .free     = mcf_gpio_free,
      .direction_input  = mcf_gpio_direction_input,
      .direction_output = mcf_gpio_direction_output,
      .get      = mcf_gpio_get_value,
      .set      = mcf_gpio_set_value_fast,
      .base     = 32,
      .ngpio      = 4,
    },
    .pddr       = (void __iomem *) MCFQADC_DDRQB,
    .podr       = (void __iomem *) MCFQADC_PORTQB,
    .ppdr       = (void __iomem *) MCFQADC_PORTQB,
  },
  {
    .gpio_chip      = {
      .label      = "A",
      .request    = mcf_gpio_request,
      .free     = mcf_gpio_free,
      .direction_input  = mcf_gpio_direction_input,
      .direction_output = mcf_gpio_direction_output,
      .get      = mcf_gpio_get_value,
      .set      = mcf_gpio_set_value_fast,
      .base     = 40,
      .ngpio      = 8,
    },
    .pddr       = (void __iomem *) MCFGPIO_DDRA,
    .podr       = (void __iomem *) MCFGPIO_PORTA,
    .ppdr       = (void __iomem *) MCFGPIO_PORTAP,
    .setr       = (void __iomem *) MCFGPIO_SETA,
    .clrr       = (void __iomem *) MCFGPIO_CLRA,
  },
  {
    .gpio_chip      = {
      .label      = "B",
      .request    = mcf_gpio_request,
      .free     = mcf_gpio_free,
      .direction_input  = mcf_gpio_direction_input,
      .direction_output = mcf_gpio_direction_output,
      .get      = mcf_gpio_get_value,
      .set      = mcf_gpio_set_value_fast,
      .base     = 48,
      .ngpio      = 8,
    },
    .pddr       = (void __iomem *) MCFGPIO_DDRB,
    .podr       = (void __iomem *) MCFGPIO_PORTB,
    .ppdr       = (void __iomem *) MCFGPIO_PORTBP,
    .setr       = (void __iomem *) MCFGPIO_SETB,
    .clrr       = (void __iomem *) MCFGPIO_CLRB,
  },
  {
    .gpio_chip      = {
      .label      = "C",
      .request    = mcf_gpio_request,
      .free     = mcf_gpio_free,
      .direction_input  = mcf_gpio_direction_input,
      .direction_output = mcf_gpio_direction_output,
      .get      = mcf_gpio_get_value,
      .set      = mcf_gpio_set_value_fast,
      .base     = 56,
      .ngpio      = 8,
    },
    .pddr       = (void __iomem *) MCFGPIO_DDRC,
    .podr       = (void __iomem *) MCFGPIO_PORTC,
    .ppdr       = (void __iomem *) MCFGPIO_PORTCP,
    .setr       = (void __iomem *) MCFGPIO_SETC,
    .clrr       = (void __iomem *) MCFGPIO_CLRC,
  },
  {
    .gpio_chip      = {
      .label      = "D",
      .request    = mcf_gpio_request,
      .free     = mcf_gpio_free,
      .direction_input  = mcf_gpio_direction_input,
      .direction_output = mcf_gpio_direction_output,
      .get      = mcf_gpio_get_value,
      .set      = mcf_gpio_set_value_fast,
      .base     = 64,
      .ngpio      = 8,
    },
    .pddr       = (void __iomem *) MCFGPIO_DDRD,
    .podr       = (void __iomem *) MCFGPIO_PORTD,
    .ppdr       = (void __iomem *) MCFGPIO_PORTDP,
    .setr       = (void __iomem *) MCFGPIO_SETD,
    .clrr       = (void __iomem *) MCFGPIO_CLRD,
  },
  {
    .gpio_chip      = {
      .label      = "E",
      .request    = mcf_gpio_request,
      .free     = mcf_gpio_free,
      .direction_input  = mcf_gpio_direction_input,
      .direction_output = mcf_gpio_direction_output,
      .get      = mcf_gpio_get_value,
      .set      = mcf_gpio_set_value_fast,
      .base     = 72,
      .ngpio      = 8,
    },
    .pddr       = (void __iomem *) MCFGPIO_DDRE,
    .podr       = (void __iomem *) MCFGPIO_PORTE,
    .ppdr       = (void __iomem *) MCFGPIO_PORTEP,
    .setr       = (void __iomem *) MCFGPIO_SETE,
    .clrr       = (void __iomem *) MCFGPIO_CLRE,
  },
  {
    .gpio_chip      = {
      .label      = "F",
      .request    = mcf_gpio_request,
      .free     = mcf_gpio_free,
      .direction_input  = mcf_gpio_direction_input,
      .direction_output = mcf_gpio_direction_output,
      .get      = mcf_gpio_get_value,
      .set      = mcf_gpio_set_value_fast,
      .base     = 80,
      .ngpio      = 8,
    },
    .pddr       = (void __iomem *) MCFGPIO_DDRF,
    .podr       = (void __iomem *) MCFGPIO_PORTF,
    .ppdr       = (void __iomem *) MCFGPIO_PORTFP,
    .setr       = (void __iomem *) MCFGPIO_SETF,
    .clrr       = (void __iomem *) MCFGPIO_CLRF,
  },
  {
    .gpio_chip      = {
      .label      = "G",
      .request    = mcf_gpio_request,
      .free     = mcf_gpio_free,
      .direction_input  = mcf_gpio_direction_input,
      .direction_output = mcf_gpio_direction_output,
      .get      = mcf_gpio_get_value,
      .set      = mcf_gpio_set_value_fast,
      .base     = 88,
      .ngpio      = 8,
    },
    .pddr       = (void __iomem *) MCFGPIO_DDRG,
    .podr       = (void __iomem *) MCFGPIO_PORTG,
    .ppdr       = (void __iomem *) MCFGPIO_PORTGP,
    .setr       = (void __iomem *) MCFGPIO_SETG,
    .clrr       = (void __iomem *) MCFGPIO_CLRG,
  },
  {
    .gpio_chip      = {
      .label      = "H",
      .request    = mcf_gpio_request,
      .free     = mcf_gpio_free,
      .direction_input  = mcf_gpio_direction_input,
      .direction_output = mcf_gpio_direction_output,
      .get      = mcf_gpio_get_value,
      .set      = mcf_gpio_set_value_fast,
      .base     = 96,
      .ngpio      = 8,
    },
    .pddr       = (void __iomem *) MCFGPIO_DDRH,
    .podr       = (void __iomem *) MCFGPIO_PORTH,
    .ppdr       = (void __iomem *) MCFGPIO_PORTHP,
    .setr       = (void __iomem *) MCFGPIO_SETH,
    .clrr       = (void __iomem *) MCFGPIO_CLRH,
  },
  {
    .gpio_chip      = {
      .label      = "J",
      .request    = mcf_gpio_request,
      .free     = mcf_gpio_free,
      .direction_input  = mcf_gpio_direction_input,
      .direction_output = mcf_gpio_direction_output,
      .get      = mcf_gpio_get_value,
      .set      = mcf_gpio_set_value_fast,
      .base     = 104,
      .ngpio      = 8,
    },
    .pddr       = (void __iomem *) MCFGPIO_DDRJ,
    .podr       = (void __iomem *) MCFGPIO_PORTJ,
    .ppdr       = (void __iomem *) MCFGPIO_PORTJP,
    .setr       = (void __iomem *) MCFGPIO_SETJ,
    .clrr       = (void __iomem *) MCFGPIO_CLRJ,
  },
  {
    .gpio_chip      = {
      .label      = "DD",
      .request    = mcf_gpio_request,
      .free     = mcf_gpio_free,
      .direction_input  = mcf_gpio_direction_input,
      .direction_output = mcf_gpio_direction_output,
      .get      = mcf_gpio_get_value,
      .set      = mcf_gpio_set_value_fast,
      .base     = 112,
      .ngpio      = 8,
    },
    .pddr       = (void __iomem *) MCFGPIO_DDRDD,
    .podr       = (void __iomem *) MCFGPIO_PORTDD,
    .ppdr       = (void __iomem *) MCFGPIO_PORTDDP,
    .setr       = (void __iomem *) MCFGPIO_SETDD,
    .clrr       = (void __iomem *) MCFGPIO_CLRDD,
  },
  {
    .gpio_chip      = {
      .label      = "EH",
      .request    = mcf_gpio_request,
      .free     = mcf_gpio_free,
      .direction_input  = mcf_gpio_direction_input,
      .direction_output = mcf_gpio_direction_output,
      .get      = mcf_gpio_get_value,
      .set      = mcf_gpio_set_value_fast,
      .base     = 120,
      .ngpio      = 8,
    },
    .pddr       = (void __iomem *) MCFGPIO_DDREH,
    .podr       = (void __iomem *) MCFGPIO_PORTEH,
    .ppdr       = (void __iomem *) MCFGPIO_PORTEHP,
    .setr       = (void __iomem *) MCFGPIO_SETEH,
    .clrr       = (void __iomem *) MCFGPIO_CLREH,
  },
  {
    .gpio_chip      = {
      .label      = "EL",
      .request    = mcf_gpio_request,
      .free     = mcf_gpio_free,
      .direction_input  = mcf_gpio_direction_input,
      .direction_output = mcf_gpio_direction_output,
      .get      = mcf_gpio_get_value,
      .set      = mcf_gpio_set_value_fast,
      .base     = 128,
      .ngpio      = 8,
    },
    .pddr       = (void __iomem *) MCFGPIO_DDREL,
    .podr       = (void __iomem *) MCFGPIO_PORTEL,
    .ppdr       = (void __iomem *) MCFGPIO_PORTELP,
    .setr       = (void __iomem *) MCFGPIO_SETEL,
    .clrr       = (void __iomem *) MCFGPIO_CLREL,
  },
  {
    .gpio_chip      = {
      .label      = "AS",
      .request    = mcf_gpio_request,
      .free     = mcf_gpio_free,
      .direction_input  = mcf_gpio_direction_input,
      .direction_output = mcf_gpio_direction_output,
      .get      = mcf_gpio_get_value,
      .set      = mcf_gpio_set_value_fast,
      .base     = 136,
      .ngpio      = 6,
    },
    .pddr       = (void __iomem *) MCFGPIO_DDRAS,
    .podr       = (void __iomem *) MCFGPIO_PORTAS,
    .ppdr       = (void __iomem *) MCFGPIO_PORTASP,
    .setr       = (void __iomem *) MCFGPIO_SETAS,
    .clrr       = (void __iomem *) MCFGPIO_CLRAS,
  },
  {
    .gpio_chip      = {
      .label      = "QS",
      .request    = mcf_gpio_request,
      .free     = mcf_gpio_free,
      .direction_input  = mcf_gpio_direction_input,
      .direction_output = mcf_gpio_direction_output,
      .get      = mcf_gpio_get_value,
      .set      = mcf_gpio_set_value_fast,
      .base     = 144,
      .ngpio      = 7,
    },
    .pddr       = (void __iomem *) MCFGPIO_DDRQS,
    .podr       = (void __iomem *) MCFGPIO_PORTQS,
    .ppdr       = (void __iomem *) MCFGPIO_PORTQSP,
    .setr       = (void __iomem *) MCFGPIO_SETQS,
    .clrr       = (void __iomem *) MCFGPIO_CLRQS,
  },
  {
    .gpio_chip      = {
      .label      = "SD",
      .request    = mcf_gpio_request,
      .free     = mcf_gpio_free,
      .direction_input  = mcf_gpio_direction_input,
      .direction_output = mcf_gpio_direction_output,
      .get      = mcf_gpio_get_value,
      .set      = mcf_gpio_set_value_fast,
      .base     = 152,
      .ngpio      = 6,
    },
    .pddr       = (void __iomem *) MCFGPIO_DDRSD,
    .podr       = (void __iomem *) MCFGPIO_PORTSD,
    .ppdr       = (void __iomem *) MCFGPIO_PORTSDP,
    .setr       = (void __iomem *) MCFGPIO_SETSD,
    .clrr       = (void __iomem *) MCFGPIO_CLRSD,
  },
  {
    .gpio_chip      = {
      .label      = "TC",
      .request    = mcf_gpio_request,
      .free     = mcf_gpio_free,
      .direction_input  = mcf_gpio_direction_input,
      .direction_output = mcf_gpio_direction_output,
      .get      = mcf_gpio_get_value,
      .set      = mcf_gpio_set_value_fast,
      .base     = 160,
      .ngpio      = 4,
    },
    .pddr       = (void __iomem *) MCFGPIO_DDRTC,
    .podr       = (void __iomem *) MCFGPIO_PORTTC,
    .ppdr       = (void __iomem *) MCFGPIO_PORTTCP,
    .setr       = (void __iomem *) MCFGPIO_SETTC,
    .clrr       = (void __iomem *) MCFGPIO_CLRTC,
  },
  {
    .gpio_chip      = {
      .label      = "TD",
      .request    = mcf_gpio_request,
      .free     = mcf_gpio_free,
      .direction_input  = mcf_gpio_direction_input,
      .direction_output = mcf_gpio_direction_output,
      .get      = mcf_gpio_get_value,
      .set      = mcf_gpio_set_value_fast,
      .base     = 168,
      .ngpio      = 4,
    },
    .pddr       = (void __iomem *) MCFGPIO_DDRTD,
    .podr       = (void __iomem *) MCFGPIO_PORTTD,
    .ppdr       = (void __iomem *) MCFGPIO_PORTTDP,
    .setr       = (void __iomem *) MCFGPIO_SETTD,
    .clrr       = (void __iomem *) MCFGPIO_CLRTD,
  },
  {
    .gpio_chip      = {
      .label      = "UA",
      .request    = mcf_gpio_request,
      .free     = mcf_gpio_free,
      .direction_input  = mcf_gpio_direction_input,
      .direction_output = mcf_gpio_direction_output,
      .get      = mcf_gpio_get_value,
      .set      = mcf_gpio_set_value_fast,
      .base     = 176,
      .ngpio      = 4,
    },
    .pddr       = (void __iomem *) MCFGPIO_DDRUA,
    .podr       = (void __iomem *) MCFGPIO_PORTUA,
    .ppdr       = (void __iomem *) MCFGPIO_PORTUAP,
    .setr       = (void __iomem *) MCFGPIO_SETUA,
    .clrr       = (void __iomem *) MCFGPIO_CLRUA,
  },
};

static int __init mcf_gpio_init (void)
{
  unsigned i = 0;
  while (i < ARRAY_SIZE (mcf_gpio_chips) )
  { (void) gpiochip_add ( (struct gpio_chip *) &mcf_gpio_chips[i++]); }
  return 0;
}

core_initcall (mcf_gpio_init);