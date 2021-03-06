<?php

/**
 * @file
 * Provide a field that attaches a Google Calendar feed.
 */
class fullcalendar_handler_field_gcal extends views_handler_field {
  function query() {
    $this->query->add_field($this->view->base_table, $this->view->base_field);
  }

  function allow_advanced_render() {
    return FALSE;
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['label'] = array('default' => $this->definition['title'], 'translatable' => TRUE);
    $options['gcal'] = array('default' => '');
    $options['class'] = array('default' => 'fc-event-default fc-event-gcal');
    $options['timezone'] = array('default' => date_default_timezone_get());
    $options['editable'] = array('default' => FALSE);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    $form['label'] = array(
      '#type' => 'textfield',
      '#title' => t('Label'),
      '#default_value' => isset($this->options['label']) ? $this->options['label'] : '',
      '#description' => t('The label for this field that will be displayed to end users if the style requires it.'),
    );
    $form['gcal'] = array(
      '#type' => 'textfield',
      '#title' => t('Feed URL'),
      '#default_value' => $this->options['gcal'],
    );
    $form['class'] = array(
      '#type' => 'textfield',
      '#title' => t('CSS Class'),
      '#default_value' => $this->options['class'],
    );
    $form['timezone'] = array(
      '#type' => 'select',
      '#title' => t('Time zone'),
      '#default_value' => $this->options['timezone'],
      '#options' => date_timezone_names(TRUE),
      '#attributes' => array('class' => array('timezone-detect')),
    );
    $form['editable'] = array(
      '#type' => 'checkbox',
      '#title' => t('Allow editing of events'),
      '#default_value' => $this->options['editable'],
    );
  }

  function render($values) {
    return array(
      $this->options['gcal'],
      array(
        'editable' => $this->options['editable'],
        'className' => $this->options['class'],
        'currentTimezone' => $this->options['timezone'],
      ),
    );
  }
}
