<?php

/**
 * @file
 * Settings form.
 */

/**
 * Admin settings form.
 */
function commerce_consignor_settings_form($form) {

  $form['commerce_consignor_actor'] = array(
    '#type' => 'textfield',
    '#title' => t('Actor'),
    '#default_value' => variable_get('commerce_consignor_actor', NULL),
  );

  $form['commerce_consignor_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Key'),
    '#default_value' => variable_get('commerce_consignor_key', NULL),
  );

  return system_settings_form($form);
}
