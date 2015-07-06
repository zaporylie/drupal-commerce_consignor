<?php

/**
 * @file
 * Add consignor related tokens to commerce-order.
 */

/**
 * Implements hook_token_info_alter().
 */
function commerce_consignor_token_info_alter(&$data) {
  $data['tokens']['commerce-order']['commerce-consignor-shipment-id'] = array(
    'name' => t("Shipment ID"),
    'description' => t("Displays shipment ID."),
  );
  $data['tokens']['commerce-order']['commerce-consignor-shipment-tracking-code'] = array(
    'name' => t("Tracking Code"),
    'description' => t("Displays shipment ID."),
  );
  $data['tokens']['commerce-order']['commerce-consignor-shipment-tracking-url'] = array(
    'name' => t("Tracking URL"),
    'description' => t("Displays shipment ID."),
  );
}

/**
 * Implements hook_tokens().
 */
function commerce_consignor_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $url_options = array('absolute' => TRUE);

  if (isset($options['language'])) {
    $url_options['language'] = $options['language'];
    $language_code = $options['language']->language;
  }
  else {
    $language_code = NULL;
  }

  $sanitize = !empty($options['sanitize']);

  $replacements = array();

  if ($type == 'commerce-order' && !empty($data['commerce-order'])) {
    $order = $data['commerce-order'];
    if (!isset($order->data['commerce_consignor']['shipment_id']) || !$shipment_id = $order->data['commerce_consignor']['shipment_id']) {
      return $replacements;
    }
    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'commerce-consignor-shipment-id':
          $replacements[$original] = $sanitize ? check_plain($shipment_id) : $shipment_id;
          break;

        case 'commerce-consignor-shipment-tracking-code':
          $tracking_code = commerce_consignor_get_tracking_code($shipment_id);
          $replacements[$original] = $sanitize ? check_plain($tracking_code) : $tracking_code;
          break;

        case 'commerce-consignor-shipment-tracking-url':
          $tracking_url = commerce_consignor_get_tracking_url($shipment_id);
          $replacements[$original] = $sanitize ? check_plain($tracking_url) : $tracking_url;
          break;
      }
    }
  }

  return $replacements;
}
